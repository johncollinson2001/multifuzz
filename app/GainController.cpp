#include "GainController.h"

// Construct
GainController::GainController(Multifuzz* plugin, MultifuzzParameterManager* parameterManager, char* name, EParameters parameter) 
	: mPlugin(plugin), mParameterManager(parameterManager), mParameter(parameter), mName(name)
{
	InitialiseParameters();

	// Register parameters with the parameter manager
	mParameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
GainController::~GainController() { }

// Process audio
void GainController::ProcessAudio(double* inL, double* inR, double* outL, double* outR) {
	// Value pointed to by output = value pointed to by input multiplied by mGain
	*outL = *inL * mGain;
	*outR = *inR * mGain;
}

// Handle parameter changes
void GainController::OnParamChange(int parameterIndex) {
	// Ensure the parameter that has changed is overdrive
	if (parameterIndex == mParameter) {
		// Set the gain member
		mGain = mPlugin->GetParam(mParameter)->DBToAmp();
	}
}

// Initialise parameters
void GainController::InitialiseParameters() {
	// Input Gain
	Parameter inputGain;
	inputGain.Id = mParameter;
	inputGain.Name = mName;
	inputGain.DefaultValue = 0.0;
	inputGain.MinValue = -48.0;
	inputGain.MaxValue = 10.0;
	inputGain.Step = 0.01;
	inputGain.Label = "db";
	inputGain.Group = "";
	inputGain.Shape = 1.0;
	mParameters.push_back(inputGain);
}