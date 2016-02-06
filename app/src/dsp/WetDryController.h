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

class WetDryController : IParameterListener
{
public:
	WetDryController(MultifuzzParameterManager* parameterManager, char* name, EParameter parameter);
	virtual ~WetDryController();
	void ProcessAudio(double dryInL, double dryInR, double wetInL, double wetInR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	double mWetDry = 0;
	EParameter mParameter;
	char* mName;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

