#include "WetDryController.h"

// Construct
WetDryController::WetDryController(MultifuzzParameterManager* parameterManager, char* name, EParameter parameter)
	: mParameter(parameter), mName(name)
{
	InitialiseParameters();

	// Register parameters with the parameter manager
	parameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
WetDryController::~WetDryController() { }

// Process audio
void WetDryController::ProcessAudio(double dryInL, double dryInR, double wetInL, double wetInR, double* outL, double* outR)
{
	double dryL = 0;
	double dryR = 0;
	double wetL = 0;
	double wetR = 0;

	// Work out the decimal percentages to apply to the inputs
	double dryMultiplier = 1 - (mWetDry / 100);
	double wetMultiplier = mWetDry / 100;

	// Apply multipliers
	dryL = dryInL * dryMultiplier;
	dryR = dryInR * dryMultiplier;
	wetL = wetInL * wetMultiplier;
	wetR = wetInR * wetMultiplier;

	// Output equals the summed wet and dry
	*outL = dryL + wetL;
	*outR = dryR + wetR;
}

// Handle parameter changes
void WetDryController::ReceiveParameterChangeNotification(int parameterIndex, double newValue)
{
	// Ensure the parameter that has changed is overdrive
	if (parameterIndex == mParameter)
	{
		// Set the gain member - convert db to amp
		mWetDry = newValue;
	}
}

// Initialise parameters
void WetDryController::InitialiseParameters()
{
	// Wet Dry
	Parameter wetDry;
	wetDry.Id = mParameter;
	wetDry.Name = mName;
	wetDry.DefaultValue = 100.0;
	wetDry.MinValue = 0.0;
	wetDry.MaxValue = 100.0;
	wetDry.Step = 0.01;
	wetDry.Label = "%";
	wetDry.Group = "";
	wetDry.Shape = 0.0;
	wetDry.Type = EParameterType::Double;
	mParameters.push_back(wetDry);
}