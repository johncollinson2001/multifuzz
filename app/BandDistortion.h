#pragma once

#include "EParameters.h"
#include "MultifuzzParameterManager.h"
#include "IAudioProcessor.h"
#include "BandPass.h"
#include "Distortion.h"

// Forward declarations
class MultifuzzParameterManager;
class BandPass;
class Distortion;

class BandDistortion : IAudioProcessor
{
public:
	BandDistortion(MultifuzzParameterManager* parameterManager, char* name, double sampleRate,
		EParameters overdriveParameter, EParameters frequencyParameter, 
		EParameters widthParameter, EParameters resonanceParameter);
	~BandDistortion();
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR);

private:
	char* mName;
	BandPass* mBandPass;
	Distortion* mDistortion;
};

