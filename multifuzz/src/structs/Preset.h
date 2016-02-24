#pragma once

#include <string>
#include "enums\EDistortionType.h"

using namespace std;

struct Preset {
	string Name;
	bool MasterBypass;
	double MasterWetDry;
	double InputGain;
	bool BandOneBypass;
	EDistortionType BandOneDistortionType;
	double BandOneOverdrive;
	double BandOneFrequency;
	double BandOneWidth;
	double BandOneResonance;
	double BandOneGain;
	bool BandTwoBypass;
	EDistortionType BandTwoDistortionType;
	double BandTwoOverdrive;
	double BandTwoFrequency;
	double BandTwoWidth;
	double BandTwoResonance;
	double BandTwoGain;
	bool BandThreeBypass;
	EDistortionType BandThreeDistortionType;
	double BandThreeOverdrive;
	double BandThreeFrequency;
	double BandThreeWidth;
	double BandThreeResonance;
	double BandThreeGain;
	double OutputGain;
};