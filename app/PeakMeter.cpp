#include "PeakMeter.h"

#include "IControl.h"

// Construct
PeakMeter::PeakMeter(IPlugBase* plugin, IRECT rectangle)
	: IControl(plugin, rectangle) { }

// Destruct
PeakMeter::~PeakMeter() { }

// Draw the control
bool PeakMeter::Draw(IGraphics* graphics)
{
	// Calculate values
	int meterHeight = mRECT.B - mRECT.T;
	int fullBlockSize = meterHeight / kNumberOfBlocks;
	int blockSize = (fullBlockSize / 3) * 2;
	int gapSize = (fullBlockSize - blockSize);

	// Calculate some position values that we'll use to track drawing locations
	int blockB = mRECT.B - (gapSize / 2);
	int blockT = blockB - blockSize;
	int blockL = mRECT.L;
	int blockR = mRECT.R;

	// Draw the blocks
	for (int i = 0; i < kNumberOfBlocks; i++) {
		// Create block rectangle
		IRECT block = IRECT(blockL, blockT, blockR, blockB);

		// Work out the color and fill the rectangle
		if (i < kLowSectionUpperBound) {
			graphics->FillIRect(&COLOR_GREEN, &block);
		} else if (i < kMidSectionUpperBound) {
			graphics->FillIRect(&COLOR_YELLOW, &block);
		} else {
			graphics->FillIRect(&COLOR_RED, &block);
		}

		// Increment position trackers
		blockB = blockT - gapSize;
		blockT = blockB - blockSize;
	}

	return true;
}

// Dirty flag
bool IsDirty() { return true; }
