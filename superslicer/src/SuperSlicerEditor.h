#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "SuperSlicer.h"

// Forward declarations
class SuperSlicer;

class SuperSlicerEditor
{
public:
	SuperSlicerEditor(SuperSlicer* plugin);
	virtual ~SuperSlicerEditor();
	IGraphics* Make(IGraphics* graphics);

private:
	SuperSlicer* mPlugin;
	void MakeBackground(IGraphics* graphics);
	void MakePowerSwitch(IGraphics* graphics);
};