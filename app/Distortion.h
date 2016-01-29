#pragma once

#include "Multifuzz.h"
#include "MultifuzzParameterManager.h"
#include "EParameters.h"
#include "Parameter.h"
#include "IParameterListener.h"
#include "IAudioProcessor.h"

class Distortion : IParameterListener, IAudioProcessor
{
public:
	Distortion(MultifuzzParameterManager* parameterManager, char* name, EParameters parameter);
	virtual ~Distortion();
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR);
	virtual void OnParamChange(int parameterIndex, double newValue);

private:
	double mOverdrive = 0;
	EParameters mParameter;
	char* mName;
	MultifuzzParameterManager* mParameterManager;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

