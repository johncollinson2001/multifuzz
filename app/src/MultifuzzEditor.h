#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Multifuzz.h"
#include "constants\LayoutConstants.h"
#include "enums\EParameter.h"
#include "structs\BandDistortionParameterSet.h"
#include "controls\PeakMeter.h"
#include "controls\MultifuzzKnob.h"
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
	int mInputPeakIdxL = 0, mInputPeakIdxR = 0, mOutputPeakIdxL = 0, mOutputPeakIdxR = 0;
	Multifuzz* mPlugin;
	void MakeBackground(IGraphics* graphics);
	void MakeHandles(IGraphics* graphics);
	void MakeTitle(IGraphics* graphics);
	void MakeGainControls(IGraphics* graphics);
	void MakeDistortionControls(IGraphics* graphics);
	void MakeBandDistortion(IGraphics* graphics, char* name, int x, BandDistortionParameterSet parameters);
	void MakeKnob(IGraphics* graphics, int x, int y, EParameter parameter, char* label);
};