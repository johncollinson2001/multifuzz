#pragma once

#include "Preset.h"

class FuzzyFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Fuzzy Fuzz";
		p.InputGain = 0;
		p.BandOneOverdrive = 40;
		p.BandOneFrequency = 130;
		p.BandOneWidth = 50;
		p.BandOneResonance = 0.6;
		p.BandTwoOverdrive = 70;
		p.BandTwoFrequency = 2400;
		p.BandTwoWidth = 500;
		p.BandTwoResonance = 0.2;
		p.BandThreeOverdrive = 40;
		p.BandThreeFrequency = 11500;
		p.BandThreeWidth = 50;
		p.BandThreeResonance = 3.4;
		p.OutputGain = -20;

		return p;
	}
};
