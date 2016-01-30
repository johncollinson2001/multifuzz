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
void Distortion::ProcessAudio(double* inL, double* inR, double* outL, double* outR) 
{
	// Value pointed to by output = value pointed to by input or overdrive
	*outL = *inL >= 0
		? fmin(*inL, mOverdrive)
		: fmin(*inL, -mOverdrive);

	*outR = *inR >= 0
		? fmin(*inR, mOverdrive)
		: fmin(*inR, -mOverdrive);

	// Increase the volumeof the saturated signal
	*outL /= mOverdrive;
	*outR /= mOverdrive;
}

// Handle parameter changes
void Distortion::OnParamChange(int parameterIndex, double newValue) 
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
	overdrive.DefaultValue = 100.0;
	overdrive.MinValue = 0.01;
	overdrive.MaxValue = 100.0;
	overdrive.Step = 0.01;
	overdrive.Label = "%";
	overdrive.Group = "";
	overdrive.Shape = 1.0;
	mParameters.push_back(overdrive);
}