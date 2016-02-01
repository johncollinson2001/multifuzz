#pragma once

#include "IControl.h"

class PeakMeter : public IControl
{
public:
	PeakMeter(IPlugBase* plugin, IRECT rectangle);
	~PeakMeter();
	virtual bool Draw(IGraphics* graphics);

private:
	const int kNumberOfBlocks = 40;
	const int kLowSectionUpperBound = 32;
	const int kMidSectionUpperBound = 36;
	const int kDbLow = -90;
	const int kDbHigh = 10;
	int mDbRange;
	double mDbRangePerBlock;
};

