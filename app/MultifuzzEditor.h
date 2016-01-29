#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Multifuzz.h"
#include "LayoutConstants.h"
#include "EParameters.h"
#include "PeakMeter.h"
#include "MultifuzzKnob.h"

// Forward declarations
class Multifuzz;

class MultifuzzEditor
{
public:
	MultifuzzEditor(Multifuzz* plugin);
	~MultifuzzEditor();
	IGraphics* Make(IGraphics* graphics);
	void NotifyOfPeakChange(double inPeakL, double inPeakR, double outPeakL, double outPeakR);

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