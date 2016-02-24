#pragma once

class IDigitalSignalProcessor
{
public:
	virtual ~IDigitalSignalProcessor() {}
	virtual void ProcessAudio(double inL, double inR, double* outL, double* outR) = 0;
};