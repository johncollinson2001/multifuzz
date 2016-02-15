#pragma once

#include "IControl.h"

class VuMeter : public IBitmapControl
{
public:
	VuMeter(IPlugBase* plugin, int x, int y, IBitmap* bitmap);
	~VuMeter();
	virtual bool Draw(IGraphics* graphics);

private:
	const int kDbLow = -50;
	const int kDbHigh = 10;
	const int kNumberOfVuSections = 6;

	// Some coefficients to use when calculating the bitmap frame during draw
	double mDbPerSection, mBitmapsPerSection;
};

