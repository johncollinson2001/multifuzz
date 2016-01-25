#pragma once

#include "resource.h"
#include <string>

using namespace std;

namespace LayoutConstants {
	// General
	const int GuiWidth = GUI_WIDTH;
	const int GuiHeight = GUI_HEIGHT;
	const string GlobalFont = "Courier New";

	// Title info
	// H1
	const int HeaderOneSize = 40;
	const string HeaderOneText = "Multifuzz";
	const int HeaderOneTop = 36;
	const int HeaderOneLeft = 100;
	const int HeaderOneBottom = 61;
	const int HeaderOneRight = 295;
	// H2
	const int HeaderTwoSize = 15;
	const string HeaderTwoText = "multi-band distortion unit";
	const int HeaderTwoTop = 68;
	const int HeaderTwoLeft = 100;
	const int HeaderTwoBottom = 83;
	const int HeaderTwoRight = 295;

	// Knob info
	const int OverdriveX = 380;
	const int OverdriveY = 220;
	const int KnobFrames = 60;
}