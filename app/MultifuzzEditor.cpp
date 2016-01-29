#include "MultifuzzEditor.h"

// Construct
MultifuzzEditor::MultifuzzEditor(Multifuzz* plugin) :
	mPlugin(plugin) { }

// Destruct
MultifuzzEditor::~MultifuzzEditor() { }

// Receive a notification that the peak values have changed
void MultifuzzEditor::NotifyOfPeakChange(double inPeakL, double inPeakR, double outPeakL, double outPeakR) {
	if (mPlugin->GetGUI())
	{
		mPlugin->GetGUI()->SetControlFromPlug(mInputPeakIdxL, inPeakL);
		mPlugin->GetGUI()->SetControlFromPlug(mInputPeakIdxR, inPeakR);
		mPlugin->GetGUI()->SetControlFromPlug(mOutputPeakIdxL, outPeakL);
		mPlugin->GetGUI()->SetControlFromPlug(mOutputPeakIdxR, outPeakR);
	}
}

// Make the editor graphics
IGraphics* MultifuzzEditor::Make(IGraphics* graphics) {
	// Make the component parts, order is essential
	MakeBackground(graphics);
	MakeHandles(graphics);
	MakeTitle(graphics);
	MakeGainControls(graphics);
	MakeDistortionControls(graphics);

	return graphics;
}

// Make the background
void MultifuzzEditor::MakeBackground(IGraphics* graphics) {
	// Tile a bitmap across the view port, to support a resizeable gui
	IBitmap bgBitmap = graphics->LoadIBitmap(BACKGROUND_ID, BACKGROUND_FN);
	for (int i = 0; i <= ceil(LayoutConstants::kGuiWidth / bgBitmap.W); i++)
	{
		int tileX = bgBitmap.W * i;
		graphics->AttachControl(new IBitmapControl(mPlugin, tileX, 0, &bgBitmap));
	}
}

// Make the handles
void MultifuzzEditor::MakeHandles(IGraphics* graphics) {
	// Create a handle at the left and right of the gui window
	IBitmap handleBitmap = graphics->LoadIBitmap(HANDLE_ID, HANDLE_FN);

	// Left
	graphics->AttachControl(new IBitmapControl(mPlugin, 0, 0, &handleBitmap));

	// Right
	int rightHandleX = (graphics->Width() - handleBitmap.W);
	graphics->AttachControl(new IBitmapControl(mPlugin, rightHandleX, 0, &handleBitmap));
}

// Make the title
void MultifuzzEditor::MakeTitle(IGraphics* graphics) {
	// Header 1
	IText h1 = IText(40, &COLOR_WHITE, "Courier New", IText::EStyle::kStyleBold);
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(100, 36, 295, 61), &h1, "Multifuzz"));

	// Header 2
	IText h2 = IText(15, &COLOR_WHITE, "Courier New");
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(100, 68, 295, 83), &h2, "multi-band distortion unit"));
}

// Make the gain controls
void MultifuzzEditor::MakeGainControls(IGraphics* graphics) {
	// Add header labels
	IText lblText = IText(16, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleNormal, IText::EAlign::kAlignCenter);

	graphics->AttachControl(new ITextControl(mPlugin, IRECT(90, 125, 195, 150), &lblText, "Input"));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(200, 125, 305, 150), &lblText, "Output"));
	
	// Attach the VU Meter bitmaps
	IBitmap vuMeterBitmap = graphics->LoadIBitmap(VUMETER_ID, VUMETER_FN);
	graphics->AttachControl(new IBitmapControl(mPlugin, 90, 152, &vuMeterBitmap));
	graphics->AttachControl(new IBitmapControl(mPlugin, 200, 152, &vuMeterBitmap));

	// Add the vu meters
	mInputPeakIdxL = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(115, 158, 136, 340)));
	mInputPeakIdxR = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(150, 158, 171, 340)));
	mOutputPeakIdxL = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(225, 158, 246, 340)));
	mOutputPeakIdxR = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(260, 158, 281, 340)));

	// Add knobs
	MakeKnob(graphics, 115, 380, EParameters::InputGain, "gain");
	MakeKnob(graphics, 225, 380, EParameters::OutputGain, "gain");
}

// Make the distortion controls
void MultifuzzEditor::MakeDistortionControls(IGraphics* graphics) {
	// Header text object
	IText lblText = IText(18, &COLOR_WHITE, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleBold, IText::EAlign::kAlignCenter);

	// Band 1 ...
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(350, 24, 414, 40), &lblText, "Band 1"));
	MakeKnob(graphics, 350, 80, EParameters::BandOneOverdrive, "overdrive");
	MakeKnob(graphics, 350, 180, EParameters::BandOneFrequency, "frequency");
	MakeKnob(graphics, 350, 280, EParameters::BandOneWidth, "width");
	MakeKnob(graphics, 350, 380, EParameters::BandOneResonance, "resonance");

	// Band 2 ...
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(450, 24, 514, 40), &lblText, "Band 2"));
	MakeKnob(graphics, 450, 80, EParameters::BandTwoOverdrive, "overdrive");
	MakeKnob(graphics, 450, 180, EParameters::BandTwoFrequency, "frequency");
	MakeKnob(graphics, 450, 280, EParameters::BandTwoWidth, "width");
	MakeKnob(graphics, 450, 380, EParameters::BandTwoResonance, "resonance");

	// Band 3 ...
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(550, 24, 614, 40), &lblText, "Band 3"));
	MakeKnob(graphics, 550, 80, EParameters::BandThreeOverdrive, "overdrive");
	MakeKnob(graphics, 550, 180, EParameters::BandThreeFrequency, "frequency");
	MakeKnob(graphics, 550, 280, EParameters::BandThreeWidth, "width");
	MakeKnob(graphics, 550, 380, EParameters::BandThreeResonance, "resonance");
}

// Make a knob
void MultifuzzEditor::MakeKnob(IGraphics* graphics, int x, int y, EParameters parameter, char* label) {
	IBitmap knob = graphics->LoadIBitmap(KNOB_ID, KNOB_FN, LayoutConstants::kKnobFrames);
	IText text = IText(16, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()));
	graphics->AttachControl(new MultifuzzKnob(mPlugin, IRECT(x, y, x + 64, y + 64 + 15), parameter, &knob, &text, label));
}