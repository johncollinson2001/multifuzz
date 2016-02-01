#pragma once

#include "IControl.h"
#include "enums\EParameters.h"

class MultifuzzKnob : public IKnobControl
{
public:
	MultifuzzKnob(IPlugBase* plugin, IRECT rectangle, EParameters parameter, IBitmap* bitmap, IText* text, char* label);
	~MultifuzzKnob();
	virtual bool Draw(IGraphics* graphics);

private:
	char* mLabel;
	IRECT mValueRectangle, mImageRectangle, mLabelRectangle;
	IBitmap mBitmap;
};

