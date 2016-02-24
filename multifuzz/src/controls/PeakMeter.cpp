#include "PeakMeter.h"

#include "IControl.h"

using namespace std;

// Construct
PeakMeter::PeakMeter(IPlugBase* plugin, IRECT rectangle)
	: IControl(plugin, rectangle), mDbRange(abs(kDbLow - kDbHigh)), 
	mDbRangePerBlock((double)mDbRange / (double)kNumberOfBlocks) 
{
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
	int gapSize = fullBlockSize - blockSize;

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
		IColor color = i < kLowSectionUpperBound
			? COLOR_GREEN
			: i < kMidSectionUpperBound
				? COLOR_YELLOW
				: COLOR_RED;

		// See if the db is greater than the lower db value of the block
		color.A = db > kDbLow + (mDbRangePerBlock * i)
			? color.A = 255 // Set opacity of block to full if so
			: color.A = 100; // Set opacity of the block to half if not
		
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
