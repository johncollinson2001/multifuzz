#pragma once

#include "IControl.h"

class PeakMeter : public IControl
{
public:
	PeakMeter(IPlugBase* plugin, IRECT rectangle);
	~PeakMeter();
	virtual bool Draw(IGraphics* graphics);

private:
	const int kNumberOfBlocks = 20;
	const int kLowSectionUpperBound = 11;
	const int kMidSectionUpperBound = 18;
	const int kDbLow = -90;
	const int kDbHigh = 10;
	int mDbRange;
	double mDbRangePerBlock;
};

