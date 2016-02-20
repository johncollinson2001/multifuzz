#include "BandDistortion.h"

// Construct
BandDistortion::BandDistortion(MultifuzzParameterManager* parameterManager, char* name,
	double sampleRate, BandDistortionParameterSet parameters)
	: mName(name), mBypassParameter(parameters.Bypass)
{
	// Setup band pass
	mBandPass = new BandPass(
		parameterManager,
		strdup((string(mName) + " Band Pass").c_str()),
		sampleRate,
		parameters.Frequency,
		parameters.Width,
		parameters.Resonance);

	// Setup distortion
	mDistortion = new Distortion(
		parameterManager,
		strdup((string(mName) + " Distortion").c_str()),
		parameters.Overdrive,
		parameters.DistortionType);

	// Setup gain controller
	mGainController = new GainController(
		parameterManager,
		strdup((string(mName) + " Gain").c_str()),
		parameters.Gain);

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
	delete mGainController;
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

		// Send audio through the gain controller
		mGainController->ProcessAudio(l, r, &l, &r);

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
	// Bypass
	Parameter bypass;
	bypass.Id = mBypassParameter;
	bypass.Name = string(mName) + " Bypass";
	bypass.DefaultValue = 0;
	bypass.Type = EParameterType::Bool;
	mParameters.push_back(bypass);
}
