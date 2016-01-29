#define _USE_MATH_DEFINES

#include "Filter.h"
#include <math.h>

// Construct
Filter::Filter(EFilterType filterType, int sampleRate, double frequency, double resonance)
	: mFilterType(filterType), mSampleRate(sampleRate), mFrequency(frequency), mResonance(resonance) {

}

// Destruct
Filter::~Filter() { }

// Process audio
void Filter::ProcessAudio(double* inL, double* inR, double* outL, double* outR) {

}

// Process a single channel
void Filter::ProcessChannel(double* in, double* out, double inputHistory[], double outputHistory[]) {

}

// Updates the coefficients that process the audio
void Filter::UpdateCoefficients() {
	double w0 = 2 * M_PI * mFrequency / mSampleRate;
	double cosw0 = cos(w0);
	double alpha = sin(w0) / (2 * mResonance);

	double b0 = 0, b1 = 0, b2 = 0, aa0 = 0, aa1 = 0, aa2 = 0;

	aa0 = 1 + alpha;
	aa1 = -2 * cosw0;
	aa2 = 1 - alpha;

	switch (mFilterType)
	{
	case EFilterType::LowPass:
		b0 = (1 - cosw0) / 2;
		b1 = 1 - cosw0;
		b2 = (1 - cosw0) / 2;
		break;
	case EFilterType::HighPass:
		b0 = (1 + cosw0) / 2;
		b1 = -(1 + cosw0);
		b2 = (1 + cosw0) / 2;
		break;
	}

	mA0 = b0 / aa0;
	mA1 = b1 / aa0;
	mA2 = b2 / aa0;
	mA3 = aa1 / aa0;
	mA4 = aa2 / aa0;
}