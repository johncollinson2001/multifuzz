#include "Multifuzz.h"
#include "IPlug_include_in_plug_src.h"

// Construct
Multifuzz::Multifuzz(IPlugInstanceInfo instanceInfo)
	: IPLUG_CTOR(EParameters::NumberOfParameters, MultifuzzPresets::kNumberOfPresets , instanceInfo),
	mMultifuzzParameterManager(new MultifuzzParameterManager(this)),
	mMultifuzzPresets(new MultifuzzPresets(this)),
	mMultifuzzEditor(new MultifuzzEditor(this)),
	mInputGainController(new GainController(this, mMultifuzzParameterManager))
{
	TRACE;	

	CreateParameters();
	CreatePresets();
	CreateGraphics();
}

// Destruct
Multifuzz::~Multifuzz() {
	delete mMultifuzzParameterManager;
	delete mMultifuzzPresets;
	delete mMultifuzzEditor;
}

// Processes audio information at the sample rate (nFrames)
void Multifuzz::ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames)
{
	// Mutex is already locked for us.

	int const channelCount = 2;

	for (int i = 0; i < channelCount; i++) {
		double* input = inputs[i];
		double* output = outputs[i];

		for (int s = 0; s < nFrames; ++s, ++input, ++output) {
			// TODO: Move into the disortion dsp class
			//if (*input >= 0) {
			//	// Make sure positive values can't go above the threshold:
			//	*output = fmin(*input, mOverdrive);
			//}
			//else {
			//	// Make sure negative values can't go below the threshold:
			//	*output = fmax(*input, -mOverdrive);
			//}
			//*output /= mOverdrive;

			*output = mInputGainController->ProcessAudio(*input);
		}
	}
}

// Triggered when sample rate changed
void Multifuzz::Reset()
{
	TRACE;
	IMutexLock lock(this);
}

// Triggered when the parameters change
void Multifuzz::OnParamChange(int parameterIndex)
{
	// Lock the thread so we can safely change values
	IMutexLock lock(this);

	// Call the parameter class to handle the change
	mMultifuzzParameterManager->OnParamChange(parameterIndex);

	// TODO: Remove once the overdrive is in its own dsp
	// See which parameter changed
	/*switch (parameterIndex)
	{
	case EParameters::Overdrive:
		mOverdrive = GetParam(EParameters::Overdrive)->Value() / 100.0;
		break;

	default:
		break;
	}*/
}

// Creates the parameters
void Multifuzz::CreateParameters() {
	// Get the parameters
	list<Parameter> parameters = mMultifuzzParameterManager->GetParameters();

	// Iterate over the parameters and make the parameter
	for (list<Parameter>::iterator iterator = parameters.begin(), end = parameters.end();
		iterator != end;
		iterator++)
	{
		Parameter parameter = (*iterator);
		GetParam(parameter.Id)->InitDouble(
			strdup(parameter.Name.c_str()),
			parameter.DefaultValue,
			parameter.MinValue,
			parameter.MaxValue,
			parameter.Step,
			strdup(parameter.Label.c_str()),
			strdup(parameter.Group.c_str()),
			parameter.Shape);
	}
}

// Creates the presets
void Multifuzz::CreatePresets() {
	// Get the presets
	list<Preset>* presets = mMultifuzzPresets->GetPresets();

	// Iterate over the presets and make the preset
	for (list<Preset>::const_iterator iterator = presets->begin(), end = presets->end();
		iterator != end;
		iterator++)
	{
		Preset preset = (*iterator);
		MakePreset(strdup(preset.Name.c_str()), preset.Overdrive);
	}
}

// Creates the graphics
void Multifuzz::CreateGraphics() {
	IGraphics* graphics = MakeGraphics(this, LayoutConstants::kGuiWidth, LayoutConstants::kGuiHeight);
	AttachGraphics(mMultifuzzEditor->Make(graphics));
}