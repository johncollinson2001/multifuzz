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
		p.BandOneOverdrive = 70;
		p.BandOneFrequency = 100;
		p.BandOneWidth = 20;
		p.BandOneResonance = 1;
		p.BandTwoBypass = 0;
		p.BandTwoOverdrive = 20;
		p.BandTwoFrequency = 4000;
		p.BandTwoWidth = 80;
		p.BandTwoResonance = 1.5;
		p.BandThreeBypass = 0;
		p.BandThreeOverdrive = 40;
		p.BandThreeFrequency = 12000;
		p.BandThreeWidth = 500;
		p.BandThreeResonance = 2;
		p.OutputGain = -20;

		return p;
	}
};
