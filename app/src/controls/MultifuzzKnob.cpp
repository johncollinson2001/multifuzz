#include "MultifuzzKnob.h"

// Construct
MultifuzzKnob::MultifuzzKnob(IPlugBase* plugin, IRECT rectangle, EParameter parameter, IBitmap* bitmap, IText* text, char* label)
	: IKnobControl(plugin, rectangle, parameter), mBitmap(*bitmap) 
{
	mText = *text;
	mDisablePrompt = false;

	// Work out the top and lower buffers allowed for the label and value, this
	// assumes the width is the exact width of the image
	int textBuffer = ((mRECT.B - mRECT.T) - (mRECT.R - mRECT.L)) / 2;

	mLabel = label;
	mLabelRectangle = IRECT(mRECT.L, mRECT.T, mRECT.R, mRECT.B);
	mValueRectangle = IRECT(mRECT.L, mRECT.B - textBuffer, mRECT.R, mRECT.B);
	mImageRectangle = IRECT(mRECT.L, mRECT.T + textBuffer, &mBitmap);
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
		graphics->DrawIText(&mText, knobValue, &mValueRectangle);
	}

	return true;
}