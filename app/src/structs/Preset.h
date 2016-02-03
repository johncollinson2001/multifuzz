#pragma once

#include <string>
#include "enums\EDistortionType.h"

using namespace std;

struct Preset {
	string Name;
	double InputGain;
	bool BandOneBypass;
	EDistortionType BandOneDistortionType;
	double BandOneOverdrive;
	double BandOneFrequency;
	double BandOneWidth;
	double BandOneResonance;
	bool BandTwoBypass;
	EDistortionType BandTwoDistortionType;
	double BandTwoOverdrive;
	double BandTwoFrequency;
	double BandTwoWidth;
	double BandTwoResonance;
	bool BandThreeBypass;
	EDistortionType BandThreeDistortionType;
	double BandThreeOverdrive;
	double BandThreeFrequency;
	double BandThreeWidth;
	double BandThreeResonance;
	double OutputGain;
};