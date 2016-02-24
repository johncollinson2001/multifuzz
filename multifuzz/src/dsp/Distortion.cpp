#define _USE_MATH_DEFINES

#include "Distortion.h"

#include <math.h>

using namespace std;

// Construct
Distortion::Distortion(MultifuzzParameterManager* parameterManager, char* name, 
	EParameter overdriveParameter, EParameter distortionTypeParameter)
	: mOverdriveParameter(overdriveParameter), mDistortionTypeParameter(distortionTypeParameter), mName(name)
{
	InitialiseParameters();

	// Register parameters with the parameter manager
	parameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
Distortion::~Distortion() { }

// Process audio
void Distortion::ProcessAudio(double inL, double inR, double* outL, double* outR) 
{
	// Ensure overdrive has been specified
	if (mOverdrive > 0)
	{
		switch(mDistortionType)
		{
		case EDistortionType::FuzzFace:
			ApplyFuzzFace(inL, inR, outL, outR);
			break;
		case EDistortionType::FuzzFactorTen:
			ApplyFuzzFactorTen(inL, inR, outL, outR);
			break;
		case EDistortionType::FurryFuzz:
			ApplyFurryFuzz(inL, inR, outL, outR);
			break;
		case EDistortionType::FuzzingAtTheMouth:
			ApplyFuzzingAtTheMouth(inL, inR, outL, outR);
			break;
		case EDistortionType::FuzzyBoots:
			ApplyFuzzyBoots(inL, inR, outL, outR);
			break;
		case EDistortionType::FuzzyFuzz:
			ApplyFuzzyFuzz(inL, inR, outL, outR);
			break;
		case EDistortionType::InYourFuzz:
			ApplyInYourFuzz(inL, inR, outL, outR);
			break;
		}		
	}
}

// Handle parameter changes
void Distortion::ReceiveParameterChangeNotification(int parameterIndex, double newValue) 
{
	// Find out what parameter has changed
	if (parameterIndex == mOverdriveParameter) 
	{
		mOverdrive = newValue;
	}
	else if (parameterIndex == mDistortionTypeParameter)
	{
		mDistortionType = (EDistortionType)((int)newValue);
	}
}

// Initialise parameters
void Distortion::InitialiseParameters() 
{
	// Overdrive
	Parameter overdrive;
	overdrive.Id = mOverdriveParameter;
	overdrive.Name = string(mName) + " Overdrive";
	overdrive.DefaultValue = 0.0;
	overdrive.MinValue = 0.0;
	overdrive.MaxValue = 100;
	overdrive.Step = 0.01;
	overdrive.Label = "%";
	overdrive.Group = "";
	overdrive.Shape = 1.0;
	overdrive.Type = EParameterType::Double;
	mParameters.push_back(overdrive);

	// Distortion Type
	Parameter distortionType;
	distortionType.Id = mDistortionTypeParameter;
	distortionType.Name = string(mName) + " Distortion Type";
	distortionType.DefaultValue = 0;
	distortionType.MinValue = 0;
	distortionType.MaxValue = EDistortionType::NumberOfDistortionTypes - 1;
	distortionType.Type = EParameterType::Int;
	mParameters.push_back(distortionType);
}

// Apply saturation to an audio signal
void Distortion::ApplyFuzzFace(double inL, double inR, double* outL, double* outR)
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

// Apply FuzzFactorTen to an audio signal
void Distortion::ApplyFuzzFactorTen(double inL, double inR, double* outL, double* outR)
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

// Apply guitar amp to an audio signal
void Distortion::ApplyFurryFuzz(double inL, double inR, double* outL, double* outR)
{
	double saturation = 0.5;

	// apply drive
	*outL = inL * mOverdrive;
	*outL /= 16;

	// apply sat
	if ((*outL - mInputHistory[0]) > saturation)
		*outL = mInputHistory[0] + saturation;
	else if ((mInputHistory[0] - *outL) > saturation)
		*outL = mInputHistory[0] - saturation;


	// apply drive
	*outR = inR *= mOverdrive;
	*outR /= 16;

	// apply sat
	if ((*outR - mInputHistory[1]) > saturation)
		*outR = mInputHistory[1] + saturation;
	else if ((mInputHistory[1] - *outR) > saturation)
		*outR = mInputHistory[1] - saturation;

	mInputHistory[0] = *outL;
	mInputHistory[1] = *outR;
}

// Apply guitar amp to an audio signal
void Distortion::ApplyInYourFuzz(double inL, double inR, double* outL, double* outR)
{
	double saturation = 
		 (mOverdrive / 10);

	*outL = pow(inL, 2) * saturation;
	*outR = pow(inR, 2) * saturation;
}

// Apply guitar amp to an audio signal
void Distortion::ApplyFuzzyFuzz(double inL, double inR, double* outL, double* outR)
{
	// Get the value that we want to limit the amplitude by
	double saturation = 1 - (mOverdrive / 100);

	// If underdrive = 0, then set it to 0.1 - we want sound to come out!
	if (saturation == 0)
	{
		saturation = 0.1;
	}

	*outL = inL / (saturation + abs(inL));
	*outR = inR / (saturation + abs(inR));
}

void Distortion::ApplyFuzzyBoots(double inL, double inR, double* outL, double* outR)
{
	double saturation =
		(mOverdrive / 10);

	*outL = inL / (sin(saturation) + abs(inL));
	*outR = inR / (sin(saturation) + abs(inR));
}

void Distortion::ApplyFuzzingAtTheMouth(double inL, double inR, double* outL, double* outR)
{
	// Get the value that we want to limit the amplitude by
	double saturation = 1 - (mOverdrive / 100);

	// If underdrive = 0, then set it to 0.1 - we want sound to come out!
	if (saturation == 0)
	{
		saturation = 0.1;
	}

	*outL = inL / (pow(inL, 2) + saturation);
	*outR = inR / (pow(inR, 2) + saturation);
}	