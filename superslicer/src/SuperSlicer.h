#pragma once

#ifndef __MULTIFUZZ__
#define __MULTIFUZZ__

#include <list>
#include "IPlug_include_in_plug_hdr.h"
#include "SuperSlicerEditor.h"
#include "constants\LayoutConstants.h"
#include "enums\EParameter.h"
#include "enums\EParameterType.h"
#include "AudioProcessor.h"

// Forward declarations
class SuperSlicerEditor;
class AudioProcessor;

class SuperSlicer : public IPlug
{
public:
	SuperSlicer(IPlugInstanceInfo instanceInfo);
	~SuperSlicer();

	void Reset();
	void OnParamChange(int parameterIndex);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);	

private:
	SuperSlicerEditor* mSuperSlicerEditor;
	AudioProcessor* mAudioProcessor;

	void CreateParameters();
	void CreatePresets();
	void CreateGraphics();
};

#endif
