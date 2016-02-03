#pragma once

#include "structs\Preset.h"

class MentalFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Mental Fuzz";
		p.InputGain = 0;
		p.BandOneBypass = 0;
		p.BandOneDistortionType = EDistortionType::WaveShaper;
		p.BandOneOverdrive = 95;
		p.BandOneFrequency = 150;
		p.BandOneWidth = 100;
		p.BandOneResonance = 2;
		p.BandTwoBypass = 0;
		p.BandTwoDistortionType = EDistortionType::WaveShaper;
		p.BandTwoOverdrive = 75;
		p.BandTwoFrequency = 1200;
		p.BandTwoWidth = 2500;
		p.BandTwoResonance = 1;
		p.BandThreeBypass = 0;
		p.BandThreeDistortionType = EDistortionType::WaveShaper;
		p.BandThreeOverdrive = 75;
		p.BandThreeFrequency = 6000;
		p.BandThreeWidth = 1000;
		p.BandThreeResonance = 3;
		p.OutputGain = -16;

		return p;
	}
};
