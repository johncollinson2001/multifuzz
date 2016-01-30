#pragma once

#include "EFilterType.h"
#include "IDigitalSignalProcessor.h"

class Filter : IDigitalSignalProcessor
{
public:
	Filter(EFilterType filterType, double sampleRate);
	virtual ~Filter();
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR);
	void SetSampleRate(double sampleRate);
	void SetFrequency(double frequency);
	void SetResonance(double resonance);

private:
	const int LowestFrequency = 20;
	const int HighestFrequency = 22000;
	double mFrequency = LowestFrequency;
	double mResonance = 0;
	double mSampleRate = 0;
	EFilterType mFilterType;

	// Array of input values, latest are in front
	double mInHistoryL[2] = {};
	double mInHistoryR[2] = {};
	// Array of output values, latest are in front
	double mOutHistoryL[2] = {};
	double mOutHistoryR[2] = {};

	// Coefficients
	double mA0 = 0, mA1 = 0, mA2 = 0, mA3 = 0, mA4 = 0;

	void ProcessChannel(double in, double* out, double inHistory[], double outHistory[]);
	void UpdateCoefficients();
};