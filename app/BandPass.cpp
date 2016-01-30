#include "BandPass.h"

using namespace std;

// Construct
BandPass::BandPass(MultifuzzParameterManager* parameterManager, char* name,
	int sampleRate, EParameters frequencyParameter,
	EParameters widthParameter, EParameters resonanceParameter)
	: mParameterManager(parameterManager), mName(name), mSampleRate(sampleRate),
	mFrequencyParameter(frequencyParameter), mWidthParameter(widthParameter), mResonanceParameter(resonanceParameter)
{
	// Create high and low pass
	mHighPassFilter = new Filter(EFilterType::HighPass, mSampleRate);
	mLowPassFilter = new Filter(EFilterType::LowPass, mSampleRate);

	// Initialise the parameters
	InitialiseParameters();

	// Register parameters with the parameter manager
	mParameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
BandPass::~BandPass() 
{
	delete mHighPassFilter;
	delete mLowPassFilter;
}

// Process audio
void BandPass::ProcessAudio(double* inL, double* inR, double* outL, double* outR)
{
	double* l = inL;
	double* r = inR;

	// Send audio through the low then high filter
	mLowPassFilter->ProcessAudio(l, r, l, r);
	mHighPassFilter->ProcessAudio(l, r, l, r);

	*outL = *l;
	*outR = *r;
}

// Handle parameter changes
void BandPass::OnParamChange(int parameterIndex, double newValue)
{
	// Find out which parameter has changed
	if (parameterIndex == mFrequencyParameter)
	{
		mFrequency = newValue;
		mHighPassFilter->SetFrequency(HighPassFrequency());
		mLowPassFilter->SetResonance(LowPassFrequency());
	}
	else if (parameterIndex == mResonanceParameter)
	{
		mResonance = newValue;
		mHighPassFilter->SetResonance(mResonance);
		mLowPassFilter->SetResonance(mResonance);
	} 
	else if (parameterIndex == mWidthParameter)
	{
		mWidth = newValue;
		mHighPassFilter->SetFrequency(HighPassFrequency());
		mLowPassFilter->SetResonance(LowPassFrequency());
	}
}

// Works out the high pass frequency of the band pass
double BandPass::LowPassFrequency()
{
	return mFrequency + (mWidth / 2);
}

// Works out the low pass frequency of the band pass
double BandPass::HighPassFrequency()
{
	return mFrequency - (mWidth / 2);
}

// Initialise parameters
void BandPass::InitialiseParameters()
{
	// Frequency
	Parameter frequency;
	frequency.Id = mFrequencyParameter;
	frequency.Name = string(mName) + " Frequency";
	frequency.DefaultValue = 1200.0;
	frequency.MinValue = 20.0;
	frequency.MaxValue = 22000.0;
	frequency.Step = 0.01;
	frequency.Label = "hz";
	frequency.Group = "";
	frequency.Shape = 1.0;
	mParameters.push_back(frequency);

	// Width
	Parameter width;
	width.Id = mWidthParameter;
	width.Name = string(mName) + " Width";
	width.DefaultValue = 100.0;
	width.MinValue = 0.1;
	width.MaxValue = 1000.0;
	width.Step = 0.01;
	width.Label = "hz";
	width.Group = "";
	width.Shape = 1.0;
	mParameters.push_back(width);

	// Resonance
	Parameter resonance;
	resonance.Id = mResonanceParameter;
	resonance.Name = string(mName) + " Resonance";
	resonance.DefaultValue = 1.0;
	resonance.MinValue = 0.1;
	resonance.MaxValue = 10.0;
	resonance.Step = 0.01;
	resonance.Label = "q";
	resonance.Group = "";
	resonance.Shape = 1.0;
	mParameters.push_back(resonance);
}