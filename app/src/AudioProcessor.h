#pragma once

#include <list>
#include "Multifuzz.h"
#include "MultifuzzParameterManager.h"
#include "enums\EParameter.h"
#include "dsp\GainController.h"
#include "dsp\BandDistortion.h"
#include "dsp\WetDryController.h"
#include "interfaces\IPeakListener.h"
#include "interfaces\IParameterListener.h"

// Forward declarations
class Multifuzz;
class MultifuzzParameterManager;
class GainController;
class BandDistortion;
class WetDryController;

class AudioProcessor : IParameterListener
{
public:
	AudioProcessor(Multifuzz* plugin, MultifuzzParameterManager* parameterManager, double sampleRate);
	~AudioProcessor();
	void ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames);
	void RegisterPeakListener(IPeakListener* listener);
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue);

private:
	static const int kNumberOfBandDistortions = 3;
	bool mBypass;
	GainController* mInputGainController;
	GainController* mOutputGainController;
	WetDryController* mWetDryController;
	BandDistortion* mBandDistortions[kNumberOfBandDistortions];
	list<IPeakListener*> mPeakListeners = list<IPeakListener*>();
	list<Parameter> mParameters = list<Parameter>();

	void SendPeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR);
	void ProcessBandDistortions(double inL, double inR, double* outL, double* outR);
	void InitialiseParameters();
};

