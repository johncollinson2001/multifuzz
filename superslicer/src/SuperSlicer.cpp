#include "SuperSlicer.h"
#include "IPlug_include_in_plug_src.h"

// Construct
SuperSlicer::SuperSlicer(IPlugInstanceInfo instanceInfo)
	: IPLUG_CTOR(EParameter::NumberOfParameters, 1, instanceInfo)	
{
	TRACE;	

	// Create the component parts of the plugin
	mAudioProcessor = new AudioProcessor(this, GetSampleRate());
	mSuperSlicerEditor = new SuperSlicerEditor(this);

	CreateParameters();
	CreateGraphics();
	CreatePresets();
}

// Destruct
SuperSlicer::~SuperSlicer() 
{
	delete mSuperSlicerEditor;
	delete mAudioProcessor;
}

// Processes audio information at the sample rate (nFrames)
void SuperSlicer::ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames)
{
	// Mutex is already locked for us.

	// Call audio processor
	mAudioProcessor->ProcessDoubleReplacing(inputs, outputs, nFrames);
}

// Triggered when sample rate changed
void SuperSlicer::Reset()
{
	TRACE;
	IMutexLock lock(this);

	// TODO: Send sample rate change to the audio processor	
}

// Triggered when the parameters change
void SuperSlicer::OnParamChange(int parameterIndex)
{
	// Lock the thread so we can safely change values
	IMutexLock lock(this);
}

// Creates the parameters
void SuperSlicer::CreateParameters() 
{
}

// Creates the presets
void SuperSlicer::CreatePresets() 
{
}

// Creates the graphics
void SuperSlicer::CreateGraphics() 
{
	IGraphics* graphics = MakeGraphics(this, LayoutConstants::kGuiWidth, LayoutConstants::kGuiHeight);
	AttachGraphics(mSuperSlicerEditor->Make(graphics));
}