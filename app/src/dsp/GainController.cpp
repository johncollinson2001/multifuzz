#include "GainController.h"

// Construct
GainController::GainController(MultifuzzParameterManager* parameterManager, char* name, EParameter parameter) 
	: mParameter(parameter), mName(name)
{
	InitialiseParameters();

	// Register parameters with the parameter manager
	parameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
GainController::~GainController() { }

// Process audio
void GainController::ProcessAudio(double inL, double inR, double* outL, double* outR) 
{
	// Value pointed to by output = value pointed to by input multiplied by mGain
	*outL = inL * mGain;
	*outR = inR * mGain;
}

// Handle parameter changes
void GainController::ReceiveParameterChangeNotification(int parameterIndex, double newValue) 
{
	// Ensure the parameter that has changed is overdrive
	if (parameterIndex == mParameter) 
	{
		// Set the gain member - convert db to amp
		mGain = (float)pow(10, (newValue / 20));
	}
}

// Initialise parameters
void GainController::InitialiseParameters() 
{
	// Gain
	Parameter gain;
	gain.Id = mParameter;
	gain.Name = mName;
	gain.DefaultValue = 0.0;
	gain.MinValue = -96.0;
	gain.MaxValue = 12.0;
	gain.Step = 0.01;
	gain.Label = "db";
	gain.Group = "";
	gain.Shape = 0.169925;
	gain.Type = EParameterType::Double;
	mParameters.push_back(gain);
}