#pragma once

#include "MultifuzzParameterManager.h"
#include "enums\EParameter.h"
#include "enums\EParameterType.h"
#include "enums\EDistortionType.h"
#include "structs\Parameter.h"
#include "interfaces\IParameterListener.h"
#include "interfaces\IDigitalSignalProcessor.h"

// Forward declarations
class MultifuzzParameterManager;

class Distortion : IParameterListener, IDigitalSignalProcessor
{
public:
	Distortion(MultifuzzParameterManager* parameterManager, char* name, EParameter overdriveParameter, EParameter distortionTypeParameter);
	virtual ~Distortion();
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	char* mName;
	double mOverdrive = 0;
	EDistortionType mDistortionType;
	EParameter mOverdriveParameter;
	EParameter mDistortionTypeParameter;
	int mInputHistory[2] = { 0, 0 }; // L&R channels
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
	void ApplyOverdrive(double inL, double inR, double* outL, double* outR);
	void ApplyWaveShaper(double inL, double inR, double* outL, double* outR);
	void ApplyGuitarAmp(double inL, double inR, double* outL, double* outR);
};

