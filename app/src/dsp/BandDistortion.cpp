#include "BandDistortion.h"

// Construct
BandDistortion::BandDistortion(MultifuzzParameterManager* parameterManager, char* name, double sampleRate,
	EParameter bypassParameter, EParameter overdriveParameter, EParameter frequencyParameter,
	EParameter widthParameter, EParameter resonanceParameter)
	: mName(name), mBypassParameter(bypassParameter)
{
	// Setup band pass
	mBandPass = new BandPass(
		parameterManager,
		strdup((string(mName) + " Band Pass").c_str()),
		sampleRate,
		frequencyParameter, widthParameter, resonanceParameter);

	// Setup distortion
	mDistortion = new Distortion(
		parameterManager,
		strdup((string(mName) + " Distortion").c_str()),
		overdriveParameter);

	// Initialise the parameters
	InitialiseParameters();

	// Register parameters with the parameter manager
	parameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
BandDistortion::~BandDistortion()
{
	delete mBandPass;
	delete mDistortion;
}

// Process audio
void BandDistortion::ProcessAudio(double inL, double inR, double* outL, double* outR)
{
	if (!mBypass)	
	{
		double l = inL;
		double r = inR;

		// Send audio through the band pass
		mBandPass->ProcessAudio(l, r, &l, &r);

		// Send audio through the distortion
		mDistortion->ProcessAudio(l, r, &l, &r);

		*outL = l;
		*outR = r;
	}
}

// Handle parameter changes
void BandDistortion::ReceiveParameterChangeNotification(int parameterIndex, double newValue)
{
	if (parameterIndex == mBypassParameter)
	{
		mBypass = newValue;
	}
}

// Initialise parameters
void BandDistortion::InitialiseParameters()
{
	// Frequency
	Parameter bypass;
	bypass.Id = mBypassParameter;
	bypass.Name = string(mName) + " Bypass";
	bypass.DefaultValue = 0;
	bypass.Type = EParameterType::Bool;
	mParameters.push_back(bypass);
}
