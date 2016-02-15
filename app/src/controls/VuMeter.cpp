#include "VuMeter.h"

// Construct
VuMeter::VuMeter(IPlugBase* plugin, int x, int y, IBitmap* bitmap)
	: IBitmapControl(plugin, x, y, bitmap),
	mBitmapsPerSection((double)mBitmap.N / (double)kNumberOfVuSections),
	mDbPerSection(abs(kDbLow - kDbHigh) / kNumberOfVuSections)
{ 
	// Set the clamp so we can receive amplitudes above 0
	Clamp(0, 10.0);
}

// Destruct
VuMeter::~VuMeter() { }

// Draws the control
bool VuMeter::Draw(IGraphics* graphics)
{
	// Get db reading of the value
	double db = AmpToDB(mValue);

	// Work out the index of the bitmap that we want to draw..
	double bitMapIndex = 0;

	// If the db is below the lower bound, set bitmap index to 1
	if (db <= kDbLow)
	{
		bitMapIndex = 1;
	}
	// If the db is above the upper bound, set bitmap index to number of frames
	else if (db >= kDbHigh)
	{
		bitMapIndex = mBitmap.N;
	}
	else
	{
		// Iterate over the VU sections
		for (int i = 0; i < kNumberOfVuSections; i++)
		{
			// Work out upper/lower limit of the vu section
			double dbSectionLowerLimit = kDbLow + (mDbPerSection * i);
			double dbSectionUpperLimit = kDbLow + (mDbPerSection * (i + 1));

			// If the db was less than the upper limit of the section
			if (db <= dbSectionUpperLimit)
			{
				// Work out how far back the db is from the upper limit
				double dbGap = db - dbSectionLowerLimit;

				// Add a number of frames to the bitmap index
				bitMapIndex += (dbGap / mDbPerSection) * mBitmapsPerSection;

				// No more looping required
				break;
			}
			else
			{
				// Db is greater than the upper limit of this section, so add
				// the bitmaps per section to the index
				bitMapIndex += mBitmapsPerSection;
			}
		}
	}

	// Draw the image bitmap
	return graphics->DrawBitmap(&mBitmap, &mRECT, round(bitMapIndex), &mBlend);
}