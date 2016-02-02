#include "MultifuzzKnob.h"

// Construct
MultifuzzKnob::MultifuzzKnob(IPlugBase* plugin, IRECT rectangle, EParameter parameter, IBitmap* bitmap, IText* text, char* label)
	: IKnobControl(plugin, rectangle, parameter), mBitmap(*bitmap) 
{
	mText = *text;
	mDisablePrompt = false;

	mLabel = label;
	mLabelRectangle = IRECT(mRECT.L, mRECT.T - 20, mRECT.R, mRECT.B);
	mValueRectangle = IRECT(mRECT.L, mRECT.B - 20, mRECT.R, mRECT.B);
	mImageRectangle = IRECT(mRECT.L, mRECT.T, &mBitmap);
}

// Destruct
MultifuzzKnob::~MultifuzzKnob() { }

// Draws the control
bool MultifuzzKnob::Draw(IGraphics* graphics)
{
	// Draw the image bitmap
	int i = 1 + int(0.5 + mValue * (double)(mBitmap.N - 1));
	i = BOUNDED(i, 1, mBitmap.N);
	graphics->DrawBitmap(&mBitmap, &mImageRectangle, i, &mBlend);

	// Draw the label
	graphics->DrawIText(&mText, mLabel, &mLabelRectangle);

	// Draw the value text
	char knobValue[20];
	mPlug->GetParam(mParamIdx)->GetDisplayForHost(knobValue);
	if (CSTR_NOT_EMPTY(knobValue))
	{		
		return graphics->DrawIText(&mText, knobValue, &mValueRectangle);
	}

	return true;
}