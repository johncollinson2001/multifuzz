#pragma once

#include <list>
#include "MultifuzzParameterManager.h"
#include "enums\EParameter.h"
#include "enums\EParameterType.h"
#include "structs\Parameter.h"
#include "interfaces\IParameterListener.h"
#include "interfaces\IDigitalSignalProcessor.h"

// Forward declarations
class MultifuzzParameterManager;

using namespace std;

class GainController : IParameterListener, IDigitalSignalProcessor
{
public:
	GainController(MultifuzzParameterManager* parameterManager, char* name, EParameter parameter);
	virtual ~GainController();
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	double mGain = 0;
	EParameter mParameter;
	char* mName;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

