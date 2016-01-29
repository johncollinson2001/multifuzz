#pragma once

class IAudioProcessor
{
public:
	virtual ~IAudioProcessor() {}
	virtual void ProcessAudio(double* inL, double* inR, double* outL, double* outR) = 0;
};