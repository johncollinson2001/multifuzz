#pragma once

#include "resource.h"
#include <string>

using namespace std;

namespace LayoutConstants 
{
	const int kGuiWidth = GUI_WIDTH;
	const int kGuiHeight = GUI_HEIGHT;

	const string kCourierNewFont = "Courier New";
	const string kTahomaFont = "Tahoma";

	const int kKnobFrames = 101;
	const int kOnOffButtonFrames = 2;
	const int kPowerSwitchFrames = 2;
	const int kVuMeterFrames = 50;

	const int kVuMeterWidth = 113; // Change to 114 for VU Meter blue
	const int kNumberOfVuSections = 6; // Change for VU Meter blue
	const int kVuDbLow = -50; // Change according to vu sections in VU meter blue
	const int kVuDbHigh = 10; // Change according to vu sections in VU meter blue

	const int kKnobMediumWidth = 52;
	const int kKnobMediumHeight = 52;

}