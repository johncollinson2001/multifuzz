#include "DistortionTypeSelector.h"

// Construct
DistortionTypeSelector::DistortionTypeSelector(IPlugBase* plugin, IRECT rectangle, EParameter parameter, IBitmap* knobBitmap, IBitmap* ledPanelBitmap)
	: IKnobControl(plugin, rectangle, parameter), mKnobBitmap(*knobBitmap), mLedPanelBitmap(*ledPanelBitmap)
{	
	mDisablePrompt = false;

	mKnobText = IText(13, &COLOR_BLACK, strdup(LayoutConstants::kCourierNewFont.c_str()));
	mLedPanelText = IText(13, &COLOR_RED, strdup(LayoutConstants::kTahomaFont.c_str()));

	mLabelRectangle = IRECT(mRECT.L + mLedPanelBitmap.W, mRECT.T - 13, mRECT.R, mRECT.B);
	mImageRectangle = IRECT(mRECT.L + mLedPanelBitmap.W, mRECT.T, &mKnobBitmap);
	mLedPanelRectangle = IRECT(mRECT.L, mRECT.T + 2, &mLedPanelBitmap);
	mLedTextRectangle = IRECT(mRECT.L, mRECT.T + 7, mRECT.L + mLedPanelBitmap.W, mRECT.B);

	// Value per type tells us how much of the knob value (0-1) is aportioned to each dist type
	// We take off one, e.g. 3 types = 0, 0.5, 1 (so value per type = 0.5)
	mValuePerType = 1.0 / (EDistortionType::NumberOfDistortionTypes - 1);
}

// Destruct
DistortionTypeSelector::~DistortionTypeSelector() { }

// Draws the control
bool DistortionTypeSelector::Draw(IGraphics* graphics)
{
	// The values below are used to enforce snapping of the knob sprite to intervals that match
	// the number of available distortion types. The selected distortion type is used to populate the 
	// text in the LED
	
	// Snapped value tells us the closest knob value for the type
	// We floor or ceil depending on which way the user is dragging
	/*double snappedValue = mValue > mPreviousValue
		? mValuePerType * (ceil(mValue / mValuePerType))
		: mValuePerType * (floor(mValue / mValuePerType));
	mPreviousValue = mValue;*/
	double snappedValue = mValuePerType * (round(mValue / mValuePerType));

	// int type value tells us the int number of the type enum that the user has selected
	int intTypeValue = snappedValue / mValuePerType;

	// Type tells us the enum value distortion type that the user has selected
	EDistortionType type = static_cast<EDistortionType>((int)(snappedValue / mValuePerType));

	// frame tells us which knob bitmap frame we need to display
	double frame = (mKnobBitmap.N / (EDistortionType::NumberOfDistortionTypes - 1)) * type;

	// Draw the image bitmap
	graphics->DrawBitmap(&mKnobBitmap, &mImageRectangle, frame, &mBlend);

	// Draw the label
	graphics->DrawIText(&mKnobText, "type", &mLabelRectangle);

	// Draw the LED Panel
	graphics->DrawBitmap(&mLedPanelBitmap, &mLedPanelRectangle, frame, &mBlend);
	graphics->DrawIText(&mLedPanelText, GetDistortionTypeLabel(type), &mLedTextRectangle);

	return true;
}

// Gets the label for a distortion type
char* DistortionTypeSelector::GetDistortionTypeLabel(EDistortionType e)
{
	switch (e)
	{
	case FurryFuzz: return "Furry Fuzz";
	case FuzzFace: return "Fuzz Face";
	case FuzzFactorTen: return "Fuzz Factor 10";
	case FuzzingAtTheMouth: return "Fuzzing at the Mouth";
	case InYourFuzz: return "In Your Fuzz";
	case FuzzyFuzz: return "Fuzzy Fuzz";
	case FuzzyBoots: return "Fuzzy Boots";
	default: "n/a";
	}
}