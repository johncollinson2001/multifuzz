#pragma once

#include <list>
#include "enums\EParameter.h"
#include "MultifuzzParameterManager.h"
#include "interfaces\IDigitalSignalProcessor.h"
#include "interfaces\IParameterListener.h"
#include "structs\Parameter.h"
#include "structs\BandDistortionParameterSet.h"
#include "dsp\BandPass.h"
#include "dsp\Distortion.h"

// Forward declarations
class MultifuzzParameterManager;
class BandPass;
class Distortion;
class GainController;

class BandDistortion : IParameterListener, IDigitalSignalProcessor
{
public:
	BandDistortion(MultifuzzParameterManager* parameterManager, char* name, 
		double sampleRate, BandDistortionParameterSet parameters);
	~BandDistortion();
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	char* mName;
	bool mBypass;
	EParameter mBypassParameter;
	BandPass* mBandPass;
	Distortion* mDistortion;
	GainController* mGainController;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

