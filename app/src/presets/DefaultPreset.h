#pragma once

#include "structs\Preset.h"
#include "enums\EDistortionType.h"

class DefaultPreset
{
public:
	static Preset Get()
	{
		Preset p;

		p.Name = "Default";
		p.MasterBypass = 0;
		p.MasterWetDry = 100;
		p.InputGain = 0;
		p.BandOneBypass = 0;
		p.BandOneDistortionType = EDistortionType::FurryFuzz;
		p.BandOneOverdrive = 100;
		p.BandOneFrequency = 1200;
		p.BandOneWidth = 1000;
		p.BandOneResonance = 1;
		p.BandTwoBypass = 1;
		p.BandTwoDistortionType = EDistortionType::FurryFuzz;
		p.BandTwoOverdrive = 0;
		p.BandTwoFrequency = 1200;
		p.BandTwoWidth = 1000;
		p.BandTwoResonance = 1;
		p.BandThreeBypass = 1;
		p.BandThreeDistortionType = EDistortionType::FurryFuzz;
		p.BandThreeOverdrive = 0;
		p.BandThreeFrequency = 1200;
		p.BandThreeWidth = 1000;
		p.BandThreeResonance = 1;
		p.OutputGain = -6;

		return p;
	}
};
