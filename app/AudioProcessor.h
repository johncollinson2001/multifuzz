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
	GainController* mInputGainController;
	GainController* mOutputGainController;
	list<BandDistortion*> mBandDistortions;
	list<IPeakListener*> mPeakListeners = list<IPeakListener*>();

	void SendPeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR);
};

