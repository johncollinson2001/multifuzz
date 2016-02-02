#pragma once

#include "MultifuzzParameterManager.h"
#include "enums\EParameter.h"
#include "enums\EParameterType.h"
#include "structs\Parameter.h"
#include "interfaces\IParameterListener.h"
#include "interfaces\IDigitalSignalProcessor.h"

// Forward declarations
class MultifuzzParameterManager;

class Distortion : IParameterListener, IDigitalSignalProcessor
{
public:
	Distortion(MultifuzzParameterManager* parameterManager, char* name, EParameter parameter);
	virtual ~Distortion();
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	double mOverdrive = 0;
	EParameter mParameter;
	char* mName;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
	void ApplySaturation(double inL, double inR, double* outL, double* outR);
	void ApplyWaveShaper(double inL, double inR, double* outL, double* outR);
};

