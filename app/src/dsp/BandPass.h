#pragma once

#include "MultifuzzParameterManager.h"
#include "enums\EParameter.h"
#include "enums\EParameterType.h"
#include "structs\Parameter.h"
#include "dsp\Filter.h"
#include "interfaces\IParameterListener.h"
#include "interfaces\IDigitalSignalProcessor.h"

// Forward declarations
class MultifuzzParameterManager;
class Filter;

class BandPass : IParameterListener, IDigitalSignalProcessor
{
public:
	BandPass(MultifuzzParameterManager* parameterManager, char* name,
		double sampleRate, EParameter frequencyParameter, 
		EParameter widthParameter, EParameter resonanceParameter);
	virtual ~BandPass();
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:	
	char* mName;
	EParameter mFrequencyParameter;
	EParameter mWidthParameter;
	EParameter mResonanceParameter;
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