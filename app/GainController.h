#pragma once

#include <list>
#include "Multifuzz.h"
#include "MultifuzzParameterManager.h"
#include "EParameters.h"
#include "Parameter.h"
#include "IParameterListener.h"

// Forward declarations
class Multifuzz;
class MultifuzzParameterManager;

using namespace std;

class GainController : IParameterListener
{
public:
	GainController(Multifuzz* plugin, MultifuzzParameterManager* parameterManager);
	virtual ~GainController();
	void ProcessAudio(double* input, double* output);
	virtual void OnParamChange(int parameterIndex);

private:
	double mGain = 0;
	Multifuzz* mPlugin;
	MultifuzzParameterManager* mParameterManager;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

