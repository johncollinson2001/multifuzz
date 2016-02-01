#pragma once

#include <string>

using namespace std;

struct Preset {
	string Name;
	double InputGain;
	double BandOneOverdrive;
	double BandOneFrequency;
	double BandOneWidth;
	double BandOneResonance;
	double BandTwoOverdrive;
	double BandTwoFrequency;
	double BandTwoWidth;
	double BandTwoResonance;
	double BandThreeOverdrive;
	double BandThreeFrequency;
	double BandThreeWidth;
	double BandThreeResonance;
	double OutputGain;
};