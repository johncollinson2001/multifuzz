#include "BandPass.h"

using namespace std;

// Construct
BandPass::BandPass(MultifuzzParameterManager* parameterManager, char* name,
	double sampleRate, EParameter frequencyParameter,
	EParameter widthParameter, EParameter resonanceParameter)
	: mName(name), mFrequencyParameter(frequencyParameter), 
	mWidthParameter(widthParameter), mResonanceParameter(resonanceParameter)
{
	// Create high and low pass
	mHighPassFilter = new Filter(EFilterType::HighPass, sampleRate);
	mLowPassFilter = new Filter(EFilterType::LowPass, sampleRate);

	// Initialise the parameters
	InitialiseParameters();

	// Register parameters with the parameter manager
	parameterManager->RegisterParameterListener(this, &mParameters);
}

// Destruct
BandPass::~BandPass() 
{
	delete mHighPassFilter;
	delete mLowPassFilter;
}

// Process audio
void BandPass::ProcessAudio(double inL, double inR, double* outL, double* outR)
{
	double l = inL;
	double r = inR;

	// Send audio through the low then high filter
	mLowPassFilter->ProcessAudio(l, r, &l, &r);
	mHighPassFilter->ProcessAudio(l, r, &l, &r);

	*outL = l;
	*outR = r;
}

// Handle parameter changes
void BandPass::ReceiveParameterChangeNotification(int parameterIndex, double newValue)
{
	// Find out which parameter has changed
	if (parameterIndex == mFrequencyParameter)
	{
		mFrequency = newValue;
		mHighPassFilter->SetFrequency(HighPassFrequency());
		mLowPassFilter->SetFrequency(LowPassFrequency());
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
		mLowPassFilter->SetFrequency(LowPassFrequency());
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
	frequency.MaxValue = 22500.0;
	frequency.Step = 0.01;
	frequency.Label = "hz";
	frequency.Group = "";
	frequency.Shape = 4.25178;
	frequency.Type = EParameterType::Double;
	mParameters.push_back(frequency);

	// Width
	Parameter width;
	width.Id = mWidthParameter;
	width.Name = string(mName) + " Width";
	width.DefaultValue = 1000;
	width.MinValue = 0.0;
	width.MaxValue = 12500.0;
	width.Step = 0.01;
	width.Label = "hz";
	width.Group = "";
	width.Shape = 3.64386;
	width.Type = EParameterType::Double;
	mParameters.push_back(width);

	// Resonance
	Parameter resonance;
	resonance.Id = mResonanceParameter;
	resonance.Name = string(mName) + " Resonance";
	resonance.DefaultValue = 2.0;
	resonance.MinValue = 1.0;
	resonance.MaxValue = 5.0;
	resonance.Step = 0.01;
	resonance.Label = "q";
	resonance.Group = "";
	resonance.Shape = 2;
	resonance.Type = EParameterType::Double;
	mParameters.push_back(resonance);
}