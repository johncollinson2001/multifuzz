#define _USE_MATH_DEFINES

#include "Distortion.h"

#include <math.h>

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
	// Ensure overdrive has been specified
	if (mOverdrive > 0)
	{
		//ApplySaturation(inL, inR, outL, outR);
		ApplyWaveShaper(inL, inR, outL, outR);
	}
}

// Handle parameter changes
void Distortion::ReceiveParameterChangeNotification(int parameterIndex, double newValue) 
{
	// Ensure the parameter that has changed is overdrive
	if (parameterIndex == mParameter) 
	{
		// Set overdrive
		mOverdrive = newValue;
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
	overdrive.MaxValue = 100;
	overdrive.Step = 0.01;
	overdrive.Label = "%";
	overdrive.Group = "";
	overdrive.Shape = 1.0;
	mParameters.push_back(overdrive);
}

// Apply saturation to an audio signal
void Distortion::ApplySaturation(double inL, double inR, double* outL, double* outR)
{
	// Get the value that we want to limit the amplitude by
	double underdrive = 1 - (mOverdrive / 100);

	// If underdrive = 0, then set it to 0.1 - we want sound to come out!
	if (underdrive == 0)
	{
		underdrive = 0.1;
	}

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

// Apply waveshaper to an audio signal
void Distortion::ApplyWaveShaper(double inL, double inR, double* outL, double* outR)
{	
	// Transform the overdrive value into the value we need to wave shape
	double waveOverdrive = mOverdrive / 10;
	if (waveOverdrive - floor(waveOverdrive) == 0)
	{
		waveOverdrive -= 0.1;
	}

	double z = M_PI * waveOverdrive;
	double s = 1 / sin(z);
	double b = 1 / waveOverdrive;

	*outL = inL > b
		? 1
		: sin(z * inL) * s;

	*outR = inR > b
		? 1
		: sin(z * inR) * s;
}