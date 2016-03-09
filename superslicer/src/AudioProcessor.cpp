#include "AudioProcessor.h"

// Construct
AudioProcessor::AudioProcessor(SuperSlicer* plugin, double sampleRate)	
{ }

// Destruct
AudioProcessor::~AudioProcessor()
{ }

// Processes audio information at the sample rate (nFrames)
void AudioProcessor::ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames)
{
	// Pull out values 
	double* inL = inputs[0];
	double* inR = inputs[1];
	double* outL = outputs[0];
	double* outR = outputs[1];
	double inPeakL = 0.0, inPeakR = 0.0, outPeakL = 0.0, outPeakR = 0.0;
		
	// Iterate samples
	for (int s = 0; s < nFrames; ++s, ++inL, ++inR, ++outL, ++outR) {
		// If by pass, set the outputs to the inputs
		if (mBypass)
		{
			*outL = *inL;
			*outR = *inR;
		}
		else
		{
			*outL = *inL;
			*outR = *inR;
		}
	}
}