#include "PeakMeter.h"

#include "IControl.h"

using namespace std;

// Construct
PeakMeter::PeakMeter(IPlugBase* plugin, IRECT rectangle)
	: IControl(plugin, rectangle), 
	mDbRange(abs(kDbLow - kDbHigh)), 
	mDbRangePerBlock(mDbRange / kNumberOfBlocks) {
	// Set the clamp so we can receive amplitudes above 0
	Clamp(0, 10.0);
}

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

	// Get the db reading of the peak amp value
	double db = AmpToDB(mValue);	

	// Draw the blocks
	for (int i = 0; i < kNumberOfBlocks; i++) {
		// Create block rectangle
		IRECT block = IRECT(blockL, blockT, blockR, blockB);

		// Work out the color and fill the rectangle
		IColor color;
		if (i < kLowSectionUpperBound) {
			color = COLOR_GREEN;			
		} else if (i < kMidSectionUpperBound) {
			color = COLOR_YELLOW;
		} else {
			color = COLOR_RED;
		}		

		// See if the db is greater than the lower db value of the block
		if (db > kDbLow + (mDbRangePerBlock * i)) {
			// Set opacity of block to full if so
			color.A = 255;
		} else {
			// Set opacity of the block to half if not
			color.A = 50;
		}
		
		// Fill the block with the color
		graphics->FillIRect(&color, &block);

		// Increment position trackers
		blockB = blockT - gapSize;
		blockT = blockB - blockSize;
	}

	return true;
}

// Dirty flag
bool IsDirty() { return true; }
