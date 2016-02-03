#pragma once

#include "structs\Preset.h"

class MegaFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Mega Fuzz";
		p.InputGain = 0;
		p.BandOneBypass = 0;
		p.BandOneDistortionType = EDistortionType::WaveShaper;
		p.BandOneOverdrive = 35;
		p.BandOneFrequency = 100;
		p.BandOneWidth = 20;
		p.BandOneResonance = 1.2;
		p.BandTwoBypass = 0;
		p.BandTwoDistortionType = EDistortionType::Overdrive;
		p.BandTwoOverdrive = 60;
		p.BandTwoFrequency = 4000;
		p.BandTwoWidth = 80;
		p.BandTwoResonance = 1.5;
		p.BandThreeBypass = 0;
		p.BandThreeDistortionType = EDistortionType::Overdrive;
		p.BandThreeOverdrive = 90;
		p.BandThreeFrequency = 12000;
		p.BandThreeWidth = 500;
		p.BandThreeResonance = 2;
		p.OutputGain = -10;

		return p;
	}
};
