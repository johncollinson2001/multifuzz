#pragma once

#include "IControl.h"
#include "constants\LayoutConstants.h"

class VuMeter : public IBitmapControl
{
public:
	VuMeter(IPlugBase* plugin, int x, int y, IBitmap* bitmap);
	~VuMeter();
	virtual bool Draw(IGraphics* graphics);

private:
	// Some coefficients to use when calculating the bitmap frame during draw
	double mDbPerSection, mBitmapsPerSection;
};

