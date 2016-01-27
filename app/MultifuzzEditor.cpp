#include "MultifuzzEditor.h"

// Construct
MultifuzzEditor::MultifuzzEditor(Multifuzz* plugin) :
	mPlugin(plugin) { }

// Destruct
MultifuzzEditor::~MultifuzzEditor() { }

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

	graphics->AttachControl(new ITextControl(mPlugin, IRECT(90, 105, 195, 125), &lblText, "Input"));
	graphics->AttachControl(new ITextControl(mPlugin, IRECT(200, 105, 305, 125), &lblText, "Output"));
	
	// Attach the VU Meter bitmaps
	IBitmap vuMeterBitmap = graphics->LoadIBitmap(VUMETER_ID, VUMETER_FN);
	graphics->AttachControl(new IBitmapControl(mPlugin, 90, 141, &vuMeterBitmap));
	graphics->AttachControl(new IBitmapControl(mPlugin, 200, 141, &vuMeterBitmap));

	// Add the vu meters
	graphics->AttachControl(new PeakMeter(mPlugin, IRECT(115, 148, 136, 329)));
	graphics->AttachControl(new PeakMeter(mPlugin, IRECT(150, 148, 171, 329)));
	graphics->AttachControl(new PeakMeter(mPlugin, IRECT(225, 148, 246, 329)));
	graphics->AttachControl(new PeakMeter(mPlugin, IRECT(260, 148, 281, 329)));

	// Add knobs
	MakeKnob(graphics, 115, 375, EParameters::InputGain, "Gain");
	MakeKnob(graphics, 225, 375, EParameters::OutputGain, "Gain");

	// Add knob titles

	// Add knob labels
	
}

// Make the distortion controls
void MultifuzzEditor::MakeDistortionControls(IGraphics* graphics) {
	MakeKnob(graphics, 380, 220, EParameters::Overdrive, "Overdrive");
}

// Make a knob
void MultifuzzEditor::MakeKnob(IGraphics* graphics, int x, int y, EParameters parameter, char* label) {
	// Create a knob bitmap and attach it to the window
	//IBitmap knob = graphics->LoadIBitmap(KNOB_ID, KNOB_FN, LayoutConstants::KnobFrames);
	//graphics->AttachControl(new IKnobMultiControl(mPlugin, x, y, parameter, &knob));

	IBitmap knob = graphics->LoadIBitmap(KNOB_ID, KNOB_FN, LayoutConstants::kKnobFrames);
	IText text = IText(14, &COLOR_BLACK, strdup(LayoutConstants::kGlobalFont.c_str()));

	graphics->AttachControl(new MultifuzzKnob(mPlugin, IRECT(x, y, x + 48, y + 48 + 20), parameter, &knob, &text, label));
}