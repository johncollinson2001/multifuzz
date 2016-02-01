#pragma once

#include "Preset.h"

class SweetyFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Sweety Fuzz";
		p.InputGain = 0;
		p.BandOneOverdrive = 20;
		p.BandOneFrequency = 200;
		p.BandOneWidth = 100;
		p.BandOneResonance = 0.5;
		p.BandTwoOverdrive = 20;
		p.BandTwoFrequency = 1200;
		p.BandTwoWidth = 100;
		p.BandTwoResonance = 1;
		p.BandThreeOverdrive = 20;
		p.BandThreeFrequency = 10000;
		p.BandThreeWidth = 100;
		p.BandThreeResonance = 1.5;
		p.OutputGain = -18;

		return p;
	}
};
