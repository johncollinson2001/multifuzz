#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Multifuzz.h"
#include "LayoutConstants.h"
#include "EParameters.h"
#include "PeakMeter.h"

// Forward declarations
class Multifuzz;

class MultifuzzEditor
{
public:
	MultifuzzEditor(Multifuzz* plugin);
	~MultifuzzEditor();
	IGraphics* Make(IGraphics* graphics);

private:
	Multifuzz* mPlugin;
	void MakeBackground(IGraphics* graphics);
	void MakeHandles(IGraphics* graphics);
	void MakeTitle(IGraphics* graphics);
	void MakeGainControls(IGraphics* graphics);
	void MakeDistortionControls(IGraphics* graphics);
	void MakeKnob(IGraphics* graphics, int x, int y, EParameters parameter);
};