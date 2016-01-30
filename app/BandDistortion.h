#pragma once

#include "EParameters.h"
#include "IAudioProcessor.h"
#include "BandPass.h"
#include "Distortion.h"

class BandDistortion : IAudioProcessor
{
public:
	BandDistortion(MultifuzzParameterManager* parameterManager, char* name, int sampleRate,
		EParameters overdriveParameter, EParameters frequencyParameter, 
		EParameters widthParameter, EParameters resonanceParameter);
	~BandDistortion();
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR);

private:
	char* mName;
	BandPass* mBandPass;
	Distortion* mDistortion;
};

