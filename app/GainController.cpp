#include "GainController.h"

// Construct
GainController::GainController(Multifuzz* plugin, MultifuzzParameterManager* parameterManager) 
	: mPlugin(plugin), mParameterManager(parameterManager)
{
	InitialiseParameters();

	// Register parameters with the parameter manager
	mParameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
GainController::~GainController() { }

// Process audio
void GainController::ProcessAudio(double* input, double* output) {
	// Value pointed to by output = value pointed to by input multiplied by mGain
	*output = *input * mGain;
}

// Handle parameter changes
void GainController::OnParamChange(int parameterIndex) {
	// Ensure the parameter that has changed is overdrive
	if (parameterIndex == EParameters::InputGain) {
		// Set the gain member
		mGain = mPlugin->GetParam(EParameters::InputGain)->DBToAmp();
	}
}

// Initialise parameters
void GainController::InitialiseParameters() {
	// Input Gain
	Parameter inputGain;
	inputGain.Id = EParameters::InputGain;
	inputGain.Name = "Input Gain";
	inputGain.DefaultValue = 0.0;
	inputGain.MinValue = -48.0;
	inputGain.MaxValue = 10.0;
	inputGain.Step = 0.01;
	inputGain.Label = "db";
	inputGain.Group = "";
	inputGain.Shape = 1.0;
	mParameters.push_back(inputGain);
}