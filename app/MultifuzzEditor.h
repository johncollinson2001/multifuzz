#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Multifuzz.h"
#include "LayoutConstants.h"
#include "EParameters.h"
#include "PeakMeter.h"
#include "MultifuzzKnob.h"
#include "AudioProcessor.h"
#include "IPeakListener.h"

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
	void MakeKnob(IGraphics* graphics, int x, int y, EParameters parameter, char* label);
};