#include "AudioProcessor.h"

// Construct
AudioProcessor::AudioProcessor(Multifuzz* plugin, MultifuzzParameterManager* parameterManager, double sampleRate)
	: mInputGainController(new GainController(parameterManager, "Input Gain", EParameter::InputGain)),
	mOutputGainController(new GainController(parameterManager, "Output Gain", EParameter::OutputGain))
{
	// Create band distortion units
	mBandDistortions[0] = new BandDistortion(
		parameterManager,
		"Band One",
		sampleRate,
		EParameter::BandOneBypass,
		EParameter::BandOneOverdrive,
		EParameter::BandOneFrequency,
		EParameter::BandOneWidth,
		EParameter::BandOneResonance);

	mBandDistortions[1] = new BandDistortion(
		parameterManager,
		"Band Two",
		sampleRate,
		EParameter::BandTwoBypass,
		EParameter::BandTwoOverdrive,
		EParameter::BandTwoFrequency,
		EParameter::BandTwoWidth,
		EParameter::BandTwoResonance);

	mBandDistortions[2] = new BandDistortion(
		parameterManager,
		"Band Three",
		sampleRate,
		EParameter::BandThreeBypass,
		EParameter::BandThreeOverdrive,
		EParameter::BandThreeFrequency,
		EParameter::BandThreeWidth,
		EParameter::BandThreeResonance);
}

// Destruct
AudioProcessor::~AudioProcessor()
{
	delete mInputGainController;
	delete mOutputGainController;

	// Iterate overthe band distortion pointers and delete them
	for (int i = 0; i < kNumberOfBandDistortions; i++)
	{
		delete mBandDistortions[i];
	}
}

// Processes audio information at the sample rate (nFrames)
void AudioProcessor::ProcessDoubleReplacing(double **inputs, double **outputs, int nFrames)
{
	// Pull out values 
	double* inL = inputs[0];
	double* inR = inputs[1];
	double* outL = outputs[0];
	double* outR = outputs[1];
	double inPeakL = 0.0, inPeakR = 0.0, outPeakL = 0.0, outPeakR = 0.0;

	// Iterate samples
	for (int s = 0; s < nFrames; ++s, ++inL, ++inR, ++outL, ++outR) {
		//// Grab the sample
		double sampleL = *inL;
		double sampleR = *inR;

		// Process input gain and capture peaks
		mInputGainController->ProcessAudio(sampleL, sampleR, &sampleL, &sampleR);
		inPeakL = IPMAX(inPeakL, fabs(sampleL));
		inPeakR = IPMAX(inPeakR, fabs(sampleR));

		//// Process band distortions
		ProcessBandDistortions(sampleL, sampleR, &sampleL, &sampleR);

		// Process output gain and capture peaks
		mOutputGainController->ProcessAudio(sampleL, sampleR, &sampleL, &sampleR);
		outPeakL = IPMAX(outPeakL, fabs(sampleL));
		outPeakR = IPMAX(outPeakR, fabs(sampleR));

		// Assign the sample to the output
		*outL = sampleL;
		*outR = sampleR;
	}

	// Send peak change notification
	SendPeakChangeNotification(inPeakL, inPeakR, outPeakL, outPeakR);
}

// Register a peak change listener with this processor
void AudioProcessor::RegisterPeakListener(IPeakListener* listener)
{
	mPeakListeners.push_back(listener);
}

// Processes the band distortions
void AudioProcessor::ProcessBandDistortions(double inL, double inR, double* outL, double* outR)
{
	double mixL = 0;
	double mixR = 0;

	// Iterate over band distortions and add the output to the mix
	for (int i = 0; i < kNumberOfBandDistortions; i++)
	{
		double l = 0;
		double r = 0;
		mBandDistortions[i]->ProcessAudio(inL, inR, &l, &r);
		mixL += l;
		mixR += r;
	}

	// Assign the mix to the output
	*outL = mixL;
	*outR = mixR;
}

// Send a peak change notification to all the listeners
void AudioProcessor::SendPeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR)
{
	// Iterate over the listeners
	for (list<IPeakListener*>::iterator iterator = mPeakListeners.begin();
	iterator != mPeakListeners.end();
		iterator++)
	{
		// Send the notification to the listener
		IPeakListener* listener = (*iterator);
		listener->ReceivePeakChangeNotification(inPeakL, inPeakR, outPeakL, outPeakR);
	}
}