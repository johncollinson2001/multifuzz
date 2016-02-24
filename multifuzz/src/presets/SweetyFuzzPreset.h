#pragma once

#include "structs\Preset.h"

class SweetyFuzzPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Sweety Fuzz";
		p.MasterBypass = 0;
		p.MasterWetDry = 100;
		p.InputGain = 0;
		p.BandOneBypass = 0;
		p.BandOneDistortionType = EDistortionType::FuzzFace;
		p.BandOneOverdrive = 90;
		p.BandOneFrequency = 200;
		p.BandOneWidth = 100;
		p.BandOneResonance = 1;
		p.BandOneGain = 0;
		p.BandTwoBypass = 0;
		p.BandTwoDistortionType = EDistortionType::FuzzFactorTen;
		p.BandTwoOverdrive = 30;
		p.BandTwoFrequency = 1200;
		p.BandTwoWidth = 100;
		p.BandTwoResonance = 2;
		p.BandTwoGain = -6;
		p.BandThreeBypass = 0;
		p.BandThreeDistortionType = EDistortionType::FuzzFace;
		p.BandThreeOverdrive = 90;
		p.BandThreeFrequency = 10000;
		p.BandThreeWidth = 100;
		p.BandThreeResonance = 1.5;
		p.BandThreeGain = 0;
		p.OutputGain = -18;

		return p;
	}
};
