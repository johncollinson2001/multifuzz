#pragma once

#include <list>
#include "MultifuzzParameterManager.h"
#include "EParameters.h"
#include "Parameter.h"
#include "IParameterListener.h"
#include "IAudioProcessor.h"

// Forward declarations
class MultifuzzParameterManager;

using namespace std;

class GainController : IParameterListener, IAudioProcessor
{
public:
	GainController(MultifuzzParameterManager* parameterManager, char* name, EParameters parameter);
	virtual ~GainController();
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	double mGain = 0;
	EParameters mParameter;
	char* mName;
	MultifuzzParameterManager* mParameterManager;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

