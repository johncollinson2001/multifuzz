#pragma once

#include "structs\Preset.h"

class MentalFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Mental Fuzz";
		p.MasterBypass = 0;
		p.MasterWetDry = 100;
		p.InputGain = 0;
		p.BandOneBypass = 0;
		p.BandOneDistortionType = EDistortionType::FuzzFactorTen;
		p.BandOneOverdrive = 95;
		p.BandOneFrequency = 150;
		p.BandOneWidth = 100;
		p.BandOneResonance = 2;
		p.BandOneGain = -6;
		p.BandTwoBypass = 0;
		p.BandTwoDistortionType = EDistortionType::FuzzFactorTen;
		p.BandTwoOverdrive = 75;
		p.BandTwoFrequency = 1200;
		p.BandTwoWidth = 2500;
		p.BandTwoResonance = 1;
		p.BandTwoGain = -6;
		p.BandThreeBypass = 0;
		p.BandThreeDistortionType = EDistortionType::FuzzFactorTen;
		p.BandThreeOverdrive = 75;
		p.BandThreeFrequency = 6000;
		p.BandThreeWidth = 1000;
		p.BandThreeResonance = 3;
		p.BandThreeGain = -6;
		p.OutputGain = -16;

		return p;
	}
};
