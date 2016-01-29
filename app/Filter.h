#pragma once

#include "Multifuzz.h"
#include "MultifuzzParameterManager.h"
#include "EParameters.h"
#include "EFilterType.h"
#include "Parameter.h"
#include "IAudioProcessor.h"

class Filter : IAudioProcessor
{
public:
	Filter(EFilterType filterType, int sampleRate, double frequency, double resonance);
	virtual ~Filter();
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR);

private:
	const int LowestFrequency = 20;
	const int HighestFrequency = 22000;
	double mFrequency = 0;
	double mResonance = 0;
	int mSampleRate = 0;
	EFilterType mFilterType;

	// Array of input values, latest are in front
	double mInputHistoryLeft[2];
	double mInputHistoryRight[2];
	// Array of output values, latest are in front
	double mOutputHistoryLeft[2];
	double mOutputHistoryRight[2];

	// Coefficients
	double mA0, mA1, mA2, mA3, mA4;

	void ProcessChannel(double* in, double* out, double inputHistory[], double outputHistory[]);
	void UpdateCoefficients();
};