#include "Distortion.h"

using namespace std;

// Construct
Distortion::Distortion(MultifuzzParameterManager* parameterManager, char* name, EParameters parameter)
	: mParameterManager(parameterManager), mParameter(parameter), mName(name)
{
	InitialiseParameters();

	// Register parameters with the parameter manager
	mParameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
Distortion::~Distortion() { }

// Process audio
void Distortion::ProcessAudio(double inL, double inR, double* outL, double* outR) 
{
	// Get the value that we want to limit the amplitude by
	double underdrive = 1 - mOverdrive;

	// Value pointed to by output = value pointed to by input or overdrive
	*outL = inL >= 0
		? fmin(inL, underdrive)
		: fmax(inL, -underdrive);

	*outR = inR >= 0
		? fmin(inR, underdrive)
		: fmax(inR, -underdrive);

	// Increase the volumeof the saturated signal
	*outL /= underdrive;
	*outR /= underdrive;
}

// Handle parameter changes
void Distortion::ReceiveParameterChangeNotification(int parameterIndex, double newValue) 
{
	// Ensure the parameter that has changed is overdrive
	if (parameterIndex == mParameter) 
	{
		// Set overdrive
		mOverdrive = newValue / 100.0;
	}
}

// Initialise parameters
void Distortion::InitialiseParameters() 
{
	// Overdrive
	Parameter overdrive;
	overdrive.Id = mParameter;
	overdrive.Name = string(mName) + " Overdrive";
	overdrive.DefaultValue = 0.0;
	overdrive.MinValue = 0.0;
	overdrive.MaxValue = 99.99;
	overdrive.Step = 0.01;
	overdrive.Label = "%";
	overdrive.Group = "";
	overdrive.Shape = 1.0;
	mParameters.push_back(overdrive);
}