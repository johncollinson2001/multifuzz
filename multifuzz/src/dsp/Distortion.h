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
	void ApplyFuzzFace(double inL, double inR, double* outL, double* outR);
	void ApplyFuzzFactorTen(double inL, double inR, double* outL, double* outR);
	void ApplyFurryFuzz(double inL, double inR, double* outL, double* outR);
	void ApplyInYourFuzz(double inL, double inR, double* outL, double* outR);
	void ApplyFuzzyFuzz(double inL, double inR, double* outL, double* outR);
	void ApplyFuzzyBoots(double inL, double inR, double* outL, double* outR);
	void ApplyFuzzingAtTheMouth(double inL, double inR, double* outL, double* outR);
};

