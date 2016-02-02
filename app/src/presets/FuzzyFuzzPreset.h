#pragma once

#include "structs\Preset.h"

class FuzzyFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Fuzzy Fuzz";
		p.InputGain = 0;
		p.BandOneBypass = 0;
		p.BandOneOverdrive = 40;
		p.BandOneFrequency = 130;
		p.BandOneWidth = 50;
		p.BandOneResonance = 1.5;
		p.BandTwoBypass = 0;
		p.BandTwoOverdrive = 70;
		p.BandTwoFrequency = 2400;
		p.BandTwoWidth = 500;
		p.BandTwoResonance = 1;
		p.BandThreeBypass = 0;
		p.BandThreeOverdrive = 40;
		p.BandThreeFrequency = 11500;
		p.BandThreeWidth = 50;
		p.BandThreeResonance = 3.4;
		p.OutputGain = -20;

		return p;
	}
};
