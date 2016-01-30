#pragma once

#include "Multifuzz.h"
#include "MultifuzzParameterManager.h"
#include "EParameters.h"
#include "Parameter.h"
#include "Filter.h"
#include "IParameterListener.h"
#include "IAudioProcessor.h"

class BandPass : IParameterListener, IAudioProcessor
{
public:
	BandPass(MultifuzzParameterManager* parameterManager, char* name,
		int sampleRate, EParameters frequencyParameter, 
		EParameters widthParameter, EParameters resonanceParameter);
	virtual ~BandPass();
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR);
	virtual void OnParamChange(int parameterIndex, double newValue);

private:	
	MultifuzzParameterManager* mParameterManager;
	char* mName;
	int mSampleRate = 0;
	EParameters mFrequencyParameter;
	EParameters mWidthParameter;
	EParameters mResonanceParameter;
	double mFrequency = 0;
	double mWidth = 0;
	double mResonance = 0;
	Filter* mHighPassFilter;
	Filter* mLowPassFilter;
	list<Parameter> mParameters = list<Parameter>();

	double LowPassFrequency();
	double HighPassFrequency();
	void InitialiseParameters();
};