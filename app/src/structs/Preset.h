#pragma once

#include <string>

using namespace std;

struct Preset {
	string Name;
	double InputGain;
	bool BandOneBypass;
	double BandOneOverdrive;
	double BandOneFrequency;
	double BandOneWidth;
	double BandOneResonance;
	bool BandTwoBypass;
	double BandTwoOverdrive;
	double BandTwoFrequency;
	double BandTwoWidth;
	double BandTwoResonance;
	bool BandThreeBypass;
	double BandThreeOverdrive;
	double BandThreeFrequency;
	double BandThreeWidth;
	double BandThreeResonance;
	double OutputGain;
};