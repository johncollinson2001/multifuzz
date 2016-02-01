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
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(100, 36, 295, 61), &h1, "Multifuzz"));

	// Header 2
	IText h2 = IText(15, &COLOR_WHITE, "Courier New");
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(100, 68, 295, 83), &h2, "multi-band distortion unit"));
}

// Make the gain controls
void MultifuzzEditor::MakeGainControls(IGraphics* graphics) 
{
	// Add header labels
	IText lblText = IText(16, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleNormal, IText::EAlign::kAlignCenter);

	graphics->AttachControl(new ITextControl(mPlugin, IRECT(90, 123, 195, 150), &lblText, "Input"));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(200, 123, 305, 150), &lblText, "Output"));
	
	// Attach the VU Meter bitmaps
	IBitmap vuMeterBitmap = graphics->LoadIBitmap(VUMETER_ID, VUMETER_FN);
	graphics->AttachControl(new IBitmapControl(mPlugin, 90, 150, &vuMeterBitmap));
	graphics->AttachControl(new IBitmapControl(mPlugin, 200, 150, &vuMeterBitmap));

	// Add the vu meters
	mInputPeakIdxL = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(115, 143, 136, 320)));
	mInputPeakIdxR = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(150, 143, 171, 320)));
	mOutputPeakIdxL = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(225, 143, 246, 320)));
	mOutputPeakIdxR = graphics->AttachControl(new PeakMeter(mPlugin, IRECT(260, 143, 281, 320)));

	// Add knobs
	MakeKnob(graphics, 111, 358, EParameters::InputGain, "gain");
	MakeKnob(graphics, 221, 358, EParameters::OutputGain, "gain");
}

// Make the distortion controls
void MultifuzzEditor::MakeDistortionControls(IGraphics* graphics) 
{
	// Header text object
	IText lblText = IText(18, &COLOR_WHITE, strdup(LayoutConstants::kGlobalFont.c_str()),
		IText::EStyle::kStyleBold, IText::EAlign::kAlignCenter);

	// Band 1 ...
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(340, 24, 404, 40), &lblText, "Band 1"));
	MakeKnob(graphics, 340, 80, EParameters::BandOneOverdrive, "overdrive");
	MakeKnob(graphics, 340, 180, EParameters::BandOneFrequency, "frequency");
	MakeKnob(graphics, 340, 280, EParameters::BandOneWidth, "width");
	MakeKnob(graphics, 340, 380, EParameters::BandOneResonance, "resonance");

	// Band 2 ...
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(440, 24, 504, 40), &lblText, "Band 2"));
	MakeKnob(graphics, 440, 80, EParameters::BandTwoOverdrive, "overdrive");
	MakeKnob(graphics, 440, 180, EParameters::BandTwoFrequency, "frequency");
	MakeKnob(graphics, 440, 280, EParameters::BandTwoWidth, "width");
	MakeKnob(graphics, 440, 380, EParameters::BandTwoResonance, "resonance");

	// Band 3 ...
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(540, 24, 604, 40), &lblText, "Band 3"));
	MakeKnob(graphics, 540, 80, EParameters::BandThreeOverdrive, "overdrive");
	MakeKnob(graphics, 540, 180, EParameters::BandThreeFrequency, "frequency");
	MakeKnob(graphics, 540, 280, EParameters::BandThreeWidth, "width");
	MakeKnob(graphics, 540, 380, EParameters::BandThreeResonance, "resonance");
}

// Make a knob
void MultifuzzEditor::MakeKnob(IGraphics* graphics, int x, int y, EParameters parameter, char* label) 
{
	IBitmap knob = graphics->LoadIBitmap(KNOB_ID, KNOB_FN, LayoutConstants::kKnobFrames);
	IText text = IText(16, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()));
	graphics->AttachControl(new MultifuzzKnob(mPlugin, IRECT(x, y, x + 64, y + 64 + 15), parameter, &knob, &text, label));
}