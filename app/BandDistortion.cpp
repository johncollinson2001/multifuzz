#include "BandDistortion.h"

// Construct
BandDistortion::BandDistortion(MultifuzzParameterManager* parameterManager, char* name, double sampleRate,
	EParameters overdriveParameter, EParameters frequencyParameter,
	EParameters widthParameter, EParameters resonanceParameter)
	: mName(name)
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
	double l = inL;
	double r = inR;

	// Send audio through the band pass
	mBandPass->ProcessAudio(l, r, &l, &r);

	// Send audio through the distortion
	mDistortion->ProcessAudio(l, r, &l, &r);

	*outL = l;
	*outR = r;
}
