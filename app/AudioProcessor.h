#pragma once

#include <list>
#include "Multifuzz.h"
#include "MultifuzzParameterManager.h"
#include "EParameters.h"
#include "GainController.h"
#include "BandDistortion.h"
#include "IPeakListener.h"

// Forward declarations
class Multifuzz;
class MultifuzzParameterManager;
class GainController;
class BandDistortion;

class AudioProcessor
{
public:
	AudioProcessor(Multifuzz* plugin, MultifuzzParameterManager* parameterManager, double sampleRate);
	~AudioProcessor();
	void ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames);
	void RegisterPeakListener(IPeakListener* listener);

private:
	static const int kNumberOfBandDistortions = 3;
	GainController* mInputGainController;
	GainController* mOutputGainController;
	BandDistortion* mBandDistortions[kNumberOfBandDistortions];
	list<IPeakListener*> mPeakListeners = list<IPeakListener*>();

	void SendPeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR);
	void ProcessBandDistortions(double inL, double inR, double* outL, double* outR);
};

