#include "MultifuzzEditor.h"

// Construct
MultifuzzEditor::MultifuzzEditor(Multifuzz* plugin) :
	mPlugin(plugin) { }

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
	for (int i = 0; i <= ceil(LayoutConstants::GuiWidth / bgBitmap.W); i++)
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
	IText h1 = IText(
		LayoutConstants::HeaderOneSize, 
		&COLOR_WHITE, 
		strdup(LayoutConstants::GlobalFont.c_str()),
		IText::EStyle::kStyleBold);

	graphics->AttachControl(new ITextControl(
		mPlugin,
		IRECT(
			LayoutConstants::HeaderOneLeft, 
			LayoutConstants::HeaderOneTop, 
			LayoutConstants::HeaderOneRight, 
			LayoutConstants::HeaderOneBottom),
		&h1,
		LayoutConstants::HeaderOneText.c_str()));

	// Header 2
	IText h2 = IText(
		LayoutConstants::HeaderTwoSize,
		&COLOR_WHITE,
		strdup(LayoutConstants::GlobalFont.c_str()));

	graphics->AttachControl(new ITextControl(
		mPlugin,
		IRECT(
			LayoutConstants::HeaderTwoLeft,
			LayoutConstants::HeaderTwoTop,
			LayoutConstants::HeaderTwoRight,
			LayoutConstants::HeaderTwoBottom),
		&h2,
		LayoutConstants::HeaderTwoText.c_str()));
}

// Make the gain controls
void MultifuzzEditor::MakeGainControls(IGraphics* graphics) {
	// Attach the VU Meter bitmaps

	// Add header labels

	// Add knobs

	// Add knob titles

	// Add knob labels
}

// Make the distortion controls
void MultifuzzEditor::MakeDistortionControls(IGraphics* graphics) {
	// Create a knob bitmap and attach it to the window
	IBitmap knob = graphics->LoadIBitmap(KNOB_ID, KNOB_FN, LayoutConstants::KnobFrames);
	graphics->AttachControl( // Pass in this and the parameter index the knob controls
		new IKnobMultiControl(mPlugin, LayoutConstants::OverdriveX, LayoutConstants::OverdriveY, EParameters::Overdrive, &knob));
}