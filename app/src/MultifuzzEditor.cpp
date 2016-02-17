#include "MultifuzzEditor.h"
#include <math.h>
#include <algorithm>

using namespace std;

// Construct
MultifuzzEditor::MultifuzzEditor(Multifuzz* plugin, AudioProcessor* audioProcessor) 
	: mPlugin(plugin) 
{ 
	// Register as a peak listener with the audio processor so we receive notifications
	// of peak changes and can update the peak meters
	audioProcessor->RegisterPeakListener(this);
}

// Destruct
MultifuzzEditor::~MultifuzzEditor() { }

// Receive a notification that the peak values have changed
void MultifuzzEditor::ReceivePeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR) 
{
	if (mPlugin->GetGUI())
	{
		mPlugin->GetGUI()->SetControlFromPlug(mInputVuMeterIdx, max(inPeakL, inPeakR));
		mPlugin->GetGUI()->SetControlFromPlug(mOutputVuMeterIdx, max(outPeakL, outPeakR));
	}
}

// Make the editor graphics
IGraphics* MultifuzzEditor::Make(IGraphics* graphics) 
{
	// Make the component parts
	MakeBackground(graphics);
	MakePowerSwitch(graphics);
	MakeGainControls(graphics);
	MakeDistortionControls(graphics);

	return graphics;
}

// Make the background
void MultifuzzEditor::MakeBackground(IGraphics* graphics) 
{
	graphics->AttachBackground(BACKGROUND_METAL_ID, BACKGROUND_METAL_FN);
}

// Make the handles
void MultifuzzEditor::MakePowerSwitch(IGraphics* graphics) 
{
	IBitmap buttonBitmap = graphics->LoadIBitmap(POWER_SWITCH_ID, POWER_SWITCH_FN, LayoutConstants::kPowerSwitchFrames);
	graphics->AttachControl(new ISwitchControl(mPlugin, 38, 25, EParameter::MasterBypass, &buttonBitmap));
}

// Make the gain controls
void MultifuzzEditor::MakeGainControls(IGraphics* graphics) 
{
	// Make in/out gain
	MakeGain(graphics, "Input", 55, EParameter::InputGain, &mInputVuMeterIdx);
	MakeGain(graphics, "Output", 215, EParameter::OutputGain, &mOutputVuMeterIdx);

	// Make wet/dry
	int knobX = 159; 
	int knobY = 290;
	int knobLabelPadding = 15;
	int knobLabelFontSize = 16;
	IRECT knobRectangle = IRECT(
		knobX,
		knobY - knobLabelPadding,
		knobX + LayoutConstants::kKnobLargeWidth,
		knobY + LayoutConstants::kKnobLargeHeight + knobLabelPadding);
	MakeKnob(graphics, KNOB_LARGE_ID, KNOB_LARGE_FN, knobRectangle, knobLabelFontSize, EParameter::MasterWetDry, "wet/dry");
}

// Make a single gain control
void MultifuzzEditor::MakeGain(IGraphics* graphics, char* name, int x, EParameter gainParameter, int* vuIdx)
{	
	int left = x;
	int right = x + LayoutConstants::kVuMeterWidth;
	int labelTop = 115; 
	int labelBottom = 140;
	int vuMeterX = x;
	int vuMeterY = 140;
	int knobX = x + (((right - left) - LayoutConstants::kKnobMediumWidth) / 2);
	int knobY = 275;
	int knobLabelPadding = 15;
	int headerLabelFontSize = 16;
	int knobLabelFontSize = 14;

	// Add header label
	IText lblText = IText(headerLabelFontSize, &COLOR_BLACK, strdup(LayoutConstants::kCourierNewFont.c_str()),
		IText::EStyle::kStyleNormal, IText::EAlign::kAlignCenter);
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(left, labelTop, right, labelBottom), &lblText, name));

	// Attach the VU Meter
	IBitmap vuMeterBitmap = graphics->LoadIBitmap(VU_METER_BLACK_ID, VU_METER_BLACK_FN, LayoutConstants::kVuMeterFrames);
	*vuIdx = graphics->AttachControl(new VuMeter(mPlugin, vuMeterX, vuMeterY, &vuMeterBitmap));

	// Add knob
	IRECT knobRectangle = IRECT(
		knobX, 
		knobY - knobLabelPadding, 
		knobX + LayoutConstants::kKnobMediumWidth, 
		knobY + LayoutConstants::kKnobMediumHeight + knobLabelPadding);
	MakeKnob(graphics, KNOB_MEDIUM_ID, KNOB_MEDIUM_FN, knobRectangle, knobLabelFontSize, gainParameter, "gain");	
}

// Make the distortion controls
void MultifuzzEditor::MakeDistortionControls(IGraphics* graphics) 
{
	MakeBandDistortion(graphics, "Band 1", 78, { 
		EParameter::BandOneBypass,
		EParameter::BandOneDistortionType,
		EParameter::BandOneOverdrive,
		EParameter::BandOneFrequency,
		EParameter::BandOneWidth,
		EParameter::BandOneResonance
	});
	MakeBandDistortion(graphics, "Band 2", 207, {
		EParameter::BandTwoBypass,
		EParameter::BandTwoDistortionType,
		EParameter::BandTwoOverdrive,
		EParameter::BandTwoFrequency,
		EParameter::BandTwoWidth,
		EParameter::BandTwoResonance
	});
	MakeBandDistortion(graphics, "Band 3", 336, {
		EParameter::BandThreeBypass,
		EParameter::BandThreeDistortionType,
		EParameter::BandThreeOverdrive,
		EParameter::BandThreeFrequency,
		EParameter::BandThreeWidth,
		EParameter::BandThreeResonance
	});
}

// Make a band distortion control unit
void MultifuzzEditor::MakeBandDistortion(IGraphics* graphics, char* name, int y, BandDistortionParameterSet parameters)
{
	int bandY = y;
	int bandX = 350;
	int headerTextL = bandX;
	int headerTextR = bandX + 70;
	int headerTextT = bandY + 7;
	int headerTextB = bandY - 7;
	int headerLabelFontSize = 17;
	int bypassX = (bandX + ((headerTextR - headerTextL) / 2)) - (LayoutConstants::kOnOffButtonWidth / 2);
	int bypassY = headerTextT - LayoutConstants::kOnOffButtonHeight;

	// Header text object	
	IText headerText = IText(headerLabelFontSize, &COLOR_BLACK, strdup(LayoutConstants::kCourierNewFont.c_str()),
		IText::EStyle::kStyleBold, IText::EAlign::kAlignCenter);
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(headerTextL, headerTextT, headerTextR, headerTextB), &headerText, name));

	// On/Off button
	IBitmap powerButtonBitmap = graphics->LoadIBitmap(ON_OFF_BUTTON_ID, ON_OFF_BUTTON_FN, LayoutConstants::kOnOffButtonFrames);	
	graphics->AttachControl(new ISwitchControl(mPlugin, bypassX, bypassY, parameters.Bypass, &powerButtonBitmap));

	// Make overdrive
	int overdriveX = headerTextR + 5;
	int overdriveY = headerTextT - 50;
	int overdriveLabelPadding = 15;
	int overdriveLabelFontSize = 16;
	IRECT overdriveRectangle = IRECT(
		overdriveX,
		overdriveY - overdriveLabelPadding,
		overdriveX + LayoutConstants::kKnobLargeWidth,
		overdriveY + LayoutConstants::kKnobLargeHeight + overdriveLabelPadding);
	MakeKnob(graphics, KNOB_LARGE_ID, KNOB_LARGE_FN, overdriveRectangle, overdriveLabelFontSize, parameters.Overdrive, "overdrive");
	
	// Make frequency/width/res/gain
	int freqRowY = headerTextB + 5;
	int freqRowX = overdriveX + LayoutConstants::kKnobLargeWidth + 10;
	int freqRowCellWidth = 67;
	int freqRowLabelPadding = 13;
	int freqRowLabelFontSize = 13;

	// Frequency
	int freqX = freqRowX + ((freqRowCellWidth - LayoutConstants::kKnobSmallWidth) / 2);
	IRECT freqRectangle = IRECT(
		freqX,
		freqRowY - freqRowLabelPadding,
		freqX + LayoutConstants::kKnobSmallWidth,
		freqRowY + LayoutConstants::kKnobSmallHeight + freqRowLabelPadding);
	MakeKnob(graphics, KNOB_SMALL_ID, KNOB_SMALL_FN, freqRectangle, freqRowLabelFontSize, parameters.Frequency, "freq");

	// Width
	int widthX = (freqRowX + freqRowCellWidth) + ((freqRowCellWidth - LayoutConstants::kKnobSmallWidth) / 2);
	IRECT widthRectangle = IRECT(
		widthX,
		freqRowY - freqRowLabelPadding,
		widthX + LayoutConstants::kKnobSmallWidth,
		freqRowY + LayoutConstants::kKnobSmallHeight + freqRowLabelPadding);
	MakeKnob(graphics, KNOB_SMALL_ID, KNOB_SMALL_FN, widthRectangle, freqRowLabelFontSize, parameters.Width, "width");

	// Res
	int resX = (freqRowX + (freqRowCellWidth * 2)) + ((freqRowCellWidth - LayoutConstants::kKnobSmallWidth) / 2);
	IRECT resRectangle = IRECT(
		resX,
		freqRowY - freqRowLabelPadding,
		resX + LayoutConstants::kKnobSmallWidth,
		freqRowY + LayoutConstants::kKnobSmallHeight + freqRowLabelPadding);
	MakeKnob(graphics, KNOB_SMALL_ID, KNOB_SMALL_FN, resRectangle, freqRowLabelFontSize, parameters.Resonance, "res");

	// Gain
	int gainX = (freqRowX + (freqRowCellWidth * 3)) + ((freqRowCellWidth - LayoutConstants::kKnobSmallWidth) / 2);
	IRECT gainRectangle = IRECT(
		gainX,
		freqRowY - freqRowLabelPadding,
		gainX + LayoutConstants::kKnobSmallWidth,
		freqRowY + LayoutConstants::kKnobSmallHeight + freqRowLabelPadding);
	MakeKnob(graphics, KNOB_SMALL_ID, KNOB_SMALL_FN, gainRectangle, freqRowLabelFontSize, parameters.Resonance, "gain");	

	// Distortion Type
	int panelX = bandX + 242;
	int panelY = bandY - 50;
	IRECT typeKnobRectangle = IRECT(
		panelX,
		panelY,
		panelX + LayoutConstants::kLedPanelWidth + LayoutConstants::kKnobMiniWidth,
		panelY + LayoutConstants::kKnobMiniHeight);

	IBitmap knob = graphics->LoadIBitmap(KNOB_MINI_ID, KNOB_MINI_FN, LayoutConstants::kKnobFrames);
	IBitmap ledPanel = graphics->LoadIBitmap(LED_PANEL_ID, LED_PANEL_FN);	
	graphics->AttachControl(new DistortionTypeSelector(mPlugin, typeKnobRectangle, parameters.DistortionType, &knob, &ledPanel));
}

// Make a knob
void MultifuzzEditor::MakeKnob(IGraphics* graphics, int bitmapId, const char* bitmapName, IRECT rect, int textSize, EParameter parameter, char* label)
{
	IBitmap knob = graphics->LoadIBitmap(bitmapId, bitmapName, LayoutConstants::kKnobFrames);
	IText text = IText(textSize, &COLOR_BLACK, strdup(LayoutConstants::kCourierNewFont.c_str()));
	graphics->AttachControl(new MultifuzzKnob(mPlugin, rect, parameter, &knob, &text, label));
}