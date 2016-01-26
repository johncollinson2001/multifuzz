#pragma once

#include "IControl.h"

class PeakMeter : public IControl
{
public:
	PeakMeter(IPlugBase* plugin, IRECT rectangle);
	~PeakMeter();
	virtual bool Draw(IGraphics* graphics);

private:
	const int NumberOfBlocks = 20;
	const int LowSectionUpperBound = 11;
	const int MidSectionUpperBound = 18;	
};

