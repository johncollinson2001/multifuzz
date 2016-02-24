#pragma once

#include "enums\EParameter.h"

struct BandDistortionParameterSet {
	EParameter Bypass;
	EParameter DistortionType;
	EParameter Overdrive;
	EParameter Frequency;
	EParameter Width;
	EParameter Resonance;
	EParameter Gain;
};