#define _USE_MATH_DEFINES

#include "Filter.h"
#include <math.h>

// Construct
Filter::Filter(EFilterType filterType, double sampleRate)
	: mFilterType(filterType), mSampleRate(sampleRate) 
{ }

// Destruct
Filter::~Filter() { }

// Process audio
void Filter::ProcessAudio(double* inL, double* inR, double* outL, double* outR) 
{
	// Process the left and right channels seperately
	ProcessChannel(inL, outL, mInHistoryL, mOutHistoryL);
	ProcessChannel(inL, outL, mInHistoryR, mOutHistoryR);
}

// Process a single channel
void Filter::ProcessChannel(double* in, double* out, double inHistory[], double outHistory[]) 
{
	// Calculate new sample
	*out = mA0 * *in
		+ mA1 * inHistory[0]
		+ mA2 * inHistory[1]
		- mA3 * outHistory[0]
		- mA4 * outHistory[1];

	// Shift along the in buffer
	inHistory[1] = inHistory[0];
	inHistory[0] = *in;

	// Shift along the out buffer            
	outHistory[1] = outHistory[0];
	outHistory[0] = *out;
}

// Sets the sample rate member
void Filter::SetSampleRate(double sampleRate) 
{
	mSampleRate = sampleRate;
	UpdateCoefficients();
}

// Sets the frequency member
void Filter::SetFrequency(double frequency) 
{
	// Ensure the frequency is set between the supported bounds
	if (frequency < LowestFrequency) 
	{
		mFrequency = LowestFrequency;
	} 
	else if (frequency > HighestFrequency) 
	{
		mFrequency = HighestFrequency;
	} 
	else
	{
		mFrequency = frequency;
	}
	
	UpdateCoefficients();
}

// Sets the resonance member
void Filter::SetResonance(double resonance) 
{
	mResonance = resonance;
	UpdateCoefficients();
}

// Updates the coefficients that process the audio
void Filter::UpdateCoefficients() 
{
	double w0 = 2 * M_PI * mFrequency / mSampleRate;
	double cosw0 = cos(w0);
	double alpha = sin(w0) / (2 * mResonance);

	double b0 = 0, b1 = 0, b2 = 0, aa0 = 0, aa1 = 0, aa2 = 0;

	aa0 = 1 + alpha;
	aa1 = -2 * cosw0;
	aa2 = 1 - alpha;

	switch (mFilterType)
	{
	case EFilterType::LowPass:
		b0 = (1 - cosw0) / 2;
		b1 = 1 - cosw0;
		b2 = (1 - cosw0) / 2;
		break;
	case EFilterType::HighPass:
		b0 = (1 + cosw0) / 2;
		b1 = -(1 + cosw0);
		b2 = (1 + cosw0) / 2;
		break;
	}

	mA0 = b0 / aa0;
	mA1 = b1 / aa0;
	mA2 = b2 / aa0;
	mA3 = aa1 / aa0;
	mA4 = aa2 / aa0;
}