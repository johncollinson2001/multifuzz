#include "Multifuzz.h"
#include "IPlug_include_in_plug_src.h"

// Construct
Multifuzz::Multifuzz(IPlugInstanceInfo instanceInfo)
	: IPLUG_CTOR(EParameters::NumberOfParameters, MultifuzzPresets::kNumberOfPresets , instanceInfo),
	mMultifuzzParameterManager(new MultifuzzParameterManager(this)),
	mMultifuzzPresets(new MultifuzzPresets(this)),
	mMultifuzzEditor(new MultifuzzEditor(this)),
	mInputGainController(new GainController(mMultifuzzParameterManager, "Input Gain", EParameters::InputGain)),
	mOutputGainController(new GainController(mMultifuzzParameterManager, "Output Gain", EParameters::OutputGain))
{
	TRACE;	

	CreateParameters();
	CreatePresets();
	CreateGraphics();
}

// Destruct
Multifuzz::~Multifuzz() 
{
	delete mMultifuzzParameterManager;
	delete mMultifuzzPresets;
	delete mMultifuzzEditor;
	delete mInputGainController;
	delete mOutputGainController;
}

// Processes audio information at the sample rate (nFrames)
void Multifuzz::ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames)
{
	// Mutex is already locked for us.
	
	// Pull out values 
	double* inL = inputs[0];
	double* inR = inputs[1];
	double* outL = outputs[0];
	double* outR = outputs[1];
	double inPeakL = 0.0, inPeakR = 0.0, outPeakL = 0.0, outPeakR = 0.0;
	
	// Iterate samples
	for (int s = 0; s < nFrames; ++s, ++inL, ++inR, ++outL, ++outR) {		
		// Grab the sample
		double* sampleL = inL;
		double* sampleR = inR;

		// Process input gain and capture peaks
		mInputGainController->ProcessAudio(sampleL, sampleR, sampleL, sampleR);
		inPeakL = IPMAX(inPeakL, fabs(*sampleL));
		inPeakR = IPMAX(inPeakR, fabs(*sampleR));

		// Process band distortions

		// Process output gain and capture peaks
		mOutputGainController->ProcessAudio(sampleL, sampleR, sampleL, sampleR);
		outPeakL = IPMAX(outPeakL, fabs(*sampleL));
		outPeakR = IPMAX(outPeakR, fabs(*sampleR));

		// Assign the sample to the output
		*outL = *sampleL;
		*outR = *sampleR;			
	}

	// Send peaks to the 
	mMultifuzzEditor->NotifyOfPeakChange(inPeakL, inPeakR, outPeakL, outPeakR);
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
		MakePreset(strdup(preset.Name.c_str()), preset.Overdrive);
	}
}

// Creates the graphics
void Multifuzz::CreateGraphics() 
{
	IGraphics* graphics = MakeGraphics(this, LayoutConstants::kGuiWidth, LayoutConstants::kGuiHeight);
	AttachGraphics(mMultifuzzEditor->Make(graphics));
}