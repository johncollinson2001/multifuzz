#include "MultifuzzEditor.h"

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
		mPlugin->GetGUI()->SetControlFromPlug(mInputPeakIdxL, inPeakL);
		mPlugin->GetGUI()->SetControlFromPlug(mInputPeakIdxR, inPeakR);
		mPlugin->GetGUI()->SetControlFromPlug(mOutputPeakIdxL, outPeakL);
		mPlugin->GetGUI()->SetControlFromPlug(mOutputPeakIdxR, outPeakR);
	}
}

// Make the editor graphics
IGraphics* MultifuzzEditor::Make(IGraphics* graphics) 
{
	// Make the component parts, order is essential
	MakeBackground(graphics);
	MakeHandles(graphics);
	MakeTitle(graphics);
	MakeGainControls(graphics);
	MakeDistortionControls(graphics);

	return graphics;
}

// Make the background
void MultifuzzEditor::MakeBackground(IGraphics* graphics) 
{
	// Tile a bitmap across the view port, to support a resizeable gui
	IBitmap bgBitmap = graphics->LoadIBitmap(BACKGROUND_ID, BACKGROUND_FN);
	for (int i = 0; i <= ceil(LayoutConstants::kGuiWidth / bgBitmap.W); i++)
	{
		int tileX = bgBitmap.W * i;
		graphics->AttachControl(new IBitmapControl(mPlugin, tileX, 0, &bgBitmap));
	}
}

// Make the handles
void MultifuzzEditor::MakeHandles(IGraphics* graphics) 
{
	// Create a handle at the left and right of the gui window
	IBitmap handleBitmap = graphics->LoadIBitmap(HANDLE_ID, HANDLE_FN);

	// Left
	graphics->AttachControl(new IBitmapControl(mPlugin, 0, 0, &handleBitmap));

	// Right
	int rightHandleX = (graphics->Width() - handleBitmap.W);
	graphics->AttachControl(new IBitmapControl(mPlugin, rightHandleX, 0, &handleBitmap));
}

// Make the title
void MultifuzzEditor::MakeTitle(IGraphics* graphics) 
{
	// Header 1
	IText h1 = IText(40, &COLOR_WHITE, "Courier New", IText::EStyle::kStyleBold);
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(120, 36, 312, 61), &h1, "Multifuzz"));

	// Header 2
	IText h2 = IText(15, &COLOR_WHITE, "Courier New");
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(120, 68, 312, 83), &h2, "multi-band distortion unit"));

	// Power Button
	IBitmap buttonBitmap = graphics->LoadIBitmap(MASTER_POWER_ID, MASTER_POWER_FN, LayoutConstants::kMasterPowerSwitchFrames);
	graphics->AttachControl(new ISwitchControl(mPlugin, 68, 20, EParameter::MasterBypass, &buttonBitmap));

}

// Make the gain controls
void MultifuzzEditor::MakeGainControls(IGraphics* graphics) 
{
	// Add header labels
	IText lblText = IText(16, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleNormal, IText::EAlign::kAlignCenter);

	graphics->AttachControl(new ITextControl(mPlugin, IRECT(89, 123, 194, 150), &lblText, "Input"));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(238, 123, 343, 150), &lblText, "Output"));
	
	// Attach the VU Meter bitmaps
	IBitmap vuMeterBitmap = graphics->LoadIBitmap(VUMETER_ID, VUMETER_FN);
	graphics->AttachControl(new IBitmapControl(mPlugin, 89, 150, &vuMeterBitmap));
	graphics->AttachControl(new IBitmapControl(mPlugin, 238, 150, &vuMeterBitmap));

	// Add the vu meters
	mInputPeakIdxL = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(114, 143, 135, 320)));
	mInputPeakIdxR = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(149, 143, 170, 320)));
	mOutputPeakIdxL = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(263, 143, 284, 320)));
	mOutputPeakIdxR = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(298, 143, 319, 320)));

	// Add knobs
	MakeKnob(graphics, 110, 358, EParameter::InputGain, "gain");
	MakeKnob(graphics, 185, 380, EParameter::MasterWetDry, "wet/dry");
	MakeKnob(graphics, 260, 358, EParameter::OutputGain, "gain");
}

// Make the distortion controls
void MultifuzzEditor::MakeDistortionControls(IGraphics* graphics) 
{
	MakeBandDistortion(graphics, "Band 1", 425, { 
		EParameter::BandOneBypass,
		EParameter::BandOneDistortionType,
		EParameter::BandOneOverdrive,
		EParameter::BandOneFrequency,
		EParameter::BandOneWidth,
		EParameter::BandOneResonance
	});
	MakeBandDistortion(graphics, "Band 2", 540, {
		EParameter::BandTwoBypass,
		EParameter::BandTwoDistortionType,
		EParameter::BandTwoOverdrive,
		EParameter::BandTwoFrequency,
		EParameter::BandTwoWidth,
		EParameter::BandTwoResonance
	});
	MakeBandDistortion(graphics, "Band 3", 655, {
		EParameter::BandThreeBypass,
		EParameter::BandThreeDistortionType,
		EParameter::BandThreeOverdrive,
		EParameter::BandThreeFrequency,
		EParameter::BandThreeWidth,
		EParameter::BandThreeResonance
	});
}

// Make a band distortion control unit
void MultifuzzEditor::MakeBandDistortion(IGraphics* graphics, char* name, int x, BandDistortionParameterSet parameters)
{
	int colL = x - 32;
	int colR = x + 32;
	int btnL = colL - 24;
	int btnR = colL - 2;
	int btnCtr = btnL + 11;

	// Header text object
	IText headerText = IText(18, &COLOR_WHITE, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleBold, IText::EAlign::kAlignCenter);
	IText distortionTypeText = IText(14, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleNormal, IText::EAlign::kAlignCenter);
	// Switch bitmaps
	IBitmap powerButtonBitmap = graphics->LoadIBitmap(POWER_ID, POWER_FN, LayoutConstants::kPowerSwitchFrames);
	IBitmap buttonBitmap = graphics->LoadIBitmap(BUTTON_ID, BUTTON_FN, LayoutConstants::kButtonFrames);

	graphics->AttachControl(new ITextControl(mPlugin, IRECT(colL, 24, colR, 40), &headerText, name));
	graphics->AttachControl(new ISwitchControl(mPlugin, btnL, 26, parameters.Bypass, &powerButtonBitmap));
	graphics->AttachControl(new IRadioButtonsControl(
		mPlugin, IRECT(btnL, 82, btnR, 142), parameters.DistortionType, 3, &buttonBitmap, EDirection::kVertical));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(btnCtr, 80, btnCtr, 93), &distortionTypeText, "ga"));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(btnCtr, 103, btnCtr, 116), &distortionTypeText, "ov"));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(btnCtr, 126, btnCtr, 139), &distortionTypeText, "ws"));
	MakeKnob(graphics, colL, 80, parameters.Overdrive, "overdrive");
	MakeKnob(graphics, colL, 180, parameters.Frequency, "frequency");
	MakeKnob(graphics, colL, 280, parameters.Width, "width");
	MakeKnob(graphics, colL, 380, parameters.Resonance, "resonance");
}

// Make a knob
void MultifuzzEditor::MakeKnob(IGraphics* graphics, int x, int y, EParameter parameter, char* label) 
{
	IBitmap knob = graphics->LoadIBitmap(KNOB_ID, KNOB_FN, LayoutConstants::kKnobFrames);
	IText text = IText(16, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()));
	graphics->AttachControl(new MultifuzzKnob(mPlugin, IRECT(x, y, x + 64, y + 64 + 15), parameter, &knob, &text, label));
}