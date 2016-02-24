#pragma once

#include "IControl.h"
#include "enums\EParameter.h"
#include "enums\EDistortionType.h"
#include "constants\LayoutConstants.h"

class DistortionTypeSelector : public IKnobControl
{
public:
	DistortionTypeSelector(IPlugBase* plugin, IRECT rectangle, EParameter parameter, IBitmap* knobBitmap, IBitmap* ledPanelBitmap);
	~DistortionTypeSelector();
	virtual bool Draw(IGraphics* graphics);

private:
	double mValuePerType;
	double mPreviousValue = 0;
	IBitmap mKnobBitmap, mLedPanelBitmap;
	IText mKnobText, mLedPanelText;
	IRECT mImageRectangle, mLabelRectangle, mLedPanelRectangle, mLedTextRectangle;

	char* GetDistortionTypeLabel(EDistortionType e);
};

