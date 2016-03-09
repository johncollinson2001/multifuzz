#include "SuperSlicerEditor.h"
#include <math.h>
#include <algorithm>

using namespace std;

// Construct
SuperSlicerEditor::SuperSlicerEditor(SuperSlicer* plugin)
	: mPlugin(plugin)
{ }

// Destruct
SuperSlicerEditor::~SuperSlicerEditor() { }

// Make the editor graphics
IGraphics* SuperSlicerEditor::Make(IGraphics* graphics) 
{
	// Make the component parts
	MakeBackground(graphics);
	MakePowerSwitch(graphics);

	return graphics;
}

// Make the background
void SuperSlicerEditor::MakeBackground(IGraphics* graphics) 
{
	graphics->AttachBackground(BACKGROUND_ID, BACKGROUND_FN);
}

// Make the handles
void SuperSlicerEditor::MakePowerSwitch(IGraphics* graphics) 
{
	IBitmap buttonBitmap = graphics->LoadIBitmap(POWER_SWITCH_ID, POWER_SWITCH_FN, LayoutConstants::kPowerSwitchFrames);
	graphics->AttachControl(new ISwitchControl(mPlugin, 38, 22, EParameter::MasterBypass, &buttonBitmap));
}