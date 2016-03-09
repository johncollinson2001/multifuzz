#pragma once

#include <list>
#include "SuperSlicer.h"

// Forward declarations
class SuperSlicer;

class AudioProcessor
{
public:
	AudioProcessor(SuperSlicer* plugin, double sampleRate);
	~AudioProcessor();
	void ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames);

private:
	bool mBypass = false;
};

