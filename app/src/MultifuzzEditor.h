#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Multifuzz.h"
#include "constants\LayoutConstants.h"
#include "enums\EParameter.h"
#include "structs\BandDistortionParameterSet.h"
#include "controls\MultifuzzKnob.h"
#include "controls\VuMeter.h"
#include "controls\DistortionTypeSelector.h"
#include "AudioProcessor.h"
#include "interfaces\IPeakListener.h"

// Forward declarations
class Multifuzz;
class AudioProcessor;

class MultifuzzEditor : IPeakListener
{
public:
	MultifuzzEditor(Multifuzz* plugin, AudioProcessor* audioProcessor);
	virtual ~MultifuzzEditor();
	IGraphics* Make(IGraphics* graphics);
	virtual void ReceivePeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR);

private:
	int mInputVuMeterIdx = 0, mOutputVuMeterIdx = 0;
	Multifuzz* mPlugin;
	void MakeBackground(IGraphics* graphics);
	void MakePowerSwitch(IGraphics* graphics);
	void MakeGainControls(IGraphics* graphics);
	void MakeGain(IGraphics* graphics, char* name, int x, EParameter gainParameter, int* vuIdx);
	void MakeDistortionControls(IGraphics* graphics);
	void MakeBandDistortion(IGraphics* graphics, char* name, int y, BandDistortionParameterSet parameters);
	void MakeKnob(IGraphics* graphics, int bitmapId, const char* bitmapName, IRECT rect, int textSize, EParameter parameter, char* label);
};