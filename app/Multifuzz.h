#pragma once

#ifndef __MULTIFUZZ__
#define __MULTIFUZZ__

#include <list>
#include "IPlug_include_in_plug_hdr.h"
#include "MultifuzzParameterManager.h"
#include "MultifuzzPresets.h"
#include "MultifuzzEditor.h"
#include "LayoutConstants.h"
#include "EParameters.h"
#include "GainController.h"

// Forward declarations
class MultifuzzEditor;
class MultifuzzPresets;
class MultifuzzParameterManager;
class GainController;

class Multifuzz : public IPlug
{
public:
	Multifuzz(IPlugInstanceInfo instanceInfo);
	~Multifuzz();

	void Reset();
	void OnParamChange(int parameterIndex);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);	

private:
	double mOverdrive = 0;
	MultifuzzParameterManager* mMultifuzzParameterManager;
	MultifuzzPresets* mMultifuzzPresets;
	MultifuzzEditor* mMultifuzzEditor;

	// DSPs - TODO: move to audio processor class
	GainController* mInputGainController;
	GainController* mOutputGainController;

	void CreateParameters();
	void CreatePresets();
	void CreateGraphics();
};

#endif
