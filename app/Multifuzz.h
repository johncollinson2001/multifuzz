#pragma once

#ifndef __MULTIFUZZ__
#define __MULTIFUZZ__

#include <list>
#include "IPlug_include_in_plug_hdr.h"
#include "MultifuzzParameters.h"
#include "MultifuzzPresets.h"
#include "MultifuzzEditor.h"
#include "LayoutConstants.h"
#include "EParameters.h"

// Forward declarations
class MultifuzzEditor;
class MultifuzzPresets;
class MultifuzzParameters;

class Multifuzz : public IPlug
{
public:
	Multifuzz(IPlugInstanceInfo instanceInfo);
	~Multifuzz();

	void Reset();
	void OnParamChange(int paramIdx);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);	

private:
	double mOverdrive = 0;
	MultifuzzParameters* mMultifuzzParameters;
	MultifuzzPresets* mMultifuzzPresets;
	MultifuzzEditor* mMultifuzzEditor;

	void CreateParameters();
	void CreatePresets();
	void CreateGraphics();
};

#endif
