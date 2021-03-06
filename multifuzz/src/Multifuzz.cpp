#include "Multifuzz.h"
#include "IPlug_include_in_plug_src.h"

// Construct
Multifuzz::Multifuzz(IPlugInstanceInfo instanceInfo)
	: IPLUG_CTOR(EParameter::NumberOfParameters, MultifuzzPresets::kNumberOfPresets , instanceInfo)	
{
	TRACE;	

	// Create the component parts of the plugin
	mMultifuzzParameterManager = new MultifuzzParameterManager(this);
	mAudioProcessor = new AudioProcessor(this, mMultifuzzParameterManager, GetSampleRate());
	mMultifuzzPresets = new MultifuzzPresets(this);
	mMultifuzzEditor = new MultifuzzEditor(this, mAudioProcessor);

	CreateParameters();
	CreateGraphics();
	CreatePresets();

	// Ensure the default preset is fully loaded when the vst opens
	RestorePreset("Default");
}

// Destruct
Multifuzz::~Multifuzz() 
{
	delete mMultifuzzParameterManager;
	delete mMultifuzzPresets;
	delete mMultifuzzEditor;
	delete mAudioProcessor;
}

// Processes audio information at the sample rate (nFrames)
void Multifuzz::ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames)
{
	// Mutex is already locked for us.

	// Call audio processor
	mAudioProcessor->ProcessDoubleReplacing(inputs, outputs, nFrames);
}

// Triggered when sample rate changed
void Multifuzz::Reset()
{
	TRACE;
	IMutexLock lock(this);

	// TODO: Send sample rate change to the audio processor	
}

// Triggered when the parameters change
void Multifuzz::OnParamChange(int parameterIndex)
{
	// Lock the thread so we can safely change values
	IMutexLock lock(this);

	// Call the parameter class to handle the change
	mMultifuzzParameterManager->SendParameterChangeNotification(parameterIndex);
}

// Creates the parameters
void Multifuzz::CreateParameters() 
{
	// Get the parameters
	list<Parameter> parameters = mMultifuzzParameterManager->GetParameters();

	// Iterate over the parameters and make the parameter
	for (list<Parameter>::iterator iterator = parameters.begin(), end = parameters.end();
		iterator != end;
		iterator++)
	{
		Parameter parameter = (*iterator);

		switch (parameter.Type)
		{
		case EParameterType::Double:
			GetParam(parameter.Id)->InitDouble(
				strdup(parameter.Name.c_str()),
				parameter.DefaultValue,
				parameter.MinValue,
				parameter.MaxValue,
				parameter.Step,
				strdup(parameter.Label.c_str()),
				strdup(parameter.Group.c_str()),
				parameter.Shape);
			break;
		case EParameterType::Bool:
			GetParam(parameter.Id)->InitBool(
				strdup(parameter.Name.c_str()),
				parameter.DefaultValue);
			break;
			case EParameterType::Int:
				GetParam(parameter.Id)->InitInt(
					strdup(parameter.Name.c_str()),
					parameter.DefaultValue,
					parameter.MinValue,
					parameter.MaxValue);
			break;
		}
	}
}

// Creates the presets
void Multifuzz::CreatePresets() 
{
	// Get the presets
	list<Preset>* presets = mMultifuzzPresets->GetPresets();

	// Iterate over the presets and make the preset
	for (list<Preset>::const_iterator iterator = presets->begin(), end = presets->end();
		iterator != end;
		iterator++)
	{
		Preset preset = (*iterator);
		MakePreset(
			strdup(preset.Name.c_str()), 
			preset.MasterBypass,
			preset.MasterWetDry,
			preset.InputGain, 
			preset.OutputGain,
			preset.BandOneBypass,
			preset.BandOneDistortionType,
			preset.BandOneOverdrive,
			preset.BandOneFrequency,
			preset.BandOneWidth,
			preset.BandOneResonance,
			preset.BandOneGain,
			preset.BandTwoBypass,
			preset.BandTwoDistortionType,
			preset.BandTwoOverdrive,
			preset.BandTwoFrequency,
			preset.BandTwoWidth,
			preset.BandTwoResonance,
			preset.BandTwoGain,
			preset.BandThreeBypass,
			preset.BandThreeDistortionType,
			preset.BandThreeOverdrive,
			preset.BandThreeFrequency,
			preset.BandThreeWidth,
			preset.BandThreeResonance,
			preset.BandThreeGain);
	}
}

// Creates the graphics
void Multifuzz::CreateGraphics() 
{
	IGraphics* graphics = MakeGraphics(this, LayoutConstants::kGuiWidth, LayoutConstants::kGuiHeight);
	AttachGraphics(mMultifuzzEditor->Make(graphics));
}