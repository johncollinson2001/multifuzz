#include "AudioProcessor.h"

// Construct
AudioProcessor::AudioProcessor(Multifuzz* plugin, MultifuzzParameterManager* parameterManager, double sampleRate)
	: mInputGainController(new GainController(parameterManager, "Input Gain", EParameters::InputGain)),
	mOutputGainController(new GainController(parameterManager, "Output Gain", EParameters::OutputGain))
{
	// Create band distortion units
	mBandDistortions.push_back(new BandDistortion(
		parameterManager, 
		"Band One",
		sampleRate,
		EParameters::BandOneOverdrive,
		EParameters::BandOneFrequency,
		EParameters::BandOneWidth,
		EParameters::BandOneResonance));

	mBandDistortions.push_back(new BandDistortion(
		parameterManager,
		"Band Two",
		sampleRate,
		EParameters::BandTwoOverdrive,
		EParameters::BandTwoFrequency,
		EParameters::BandTwoWidth,
		EParameters::BandTwoResonance));

	mBandDistortions.push_back(new BandDistortion(
		parameterManager,
		"Band Three",
		sampleRate,
		EParameters::BandThreeOverdrive,
		EParameters::BandThreeFrequency,
		EParameters::BandThreeWidth,
		EParameters::BandThreeResonance));
}

// Destruct
AudioProcessor::~AudioProcessor()
{
	delete mInputGainController;
	delete mOutputGainController;

	// Iterate overthe band distortion pointers and delete them
	for (list<BandDistortion*>::iterator iterator = mBandDistortions.begin();
		iterator != mBandDistortions.end();
		iterator++)
	{
		BandDistortion* bandDistortion = (*iterator);
		delete bandDistortion;
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
		//// Iterate over the band distortion pointers and process them
		///*for (list<BandDistortion*>::iterator iterator = mBandDistortions.begin();
		//iterator != mBandDistortions.end();
		//	iterator++)
		//{
		//	BandDistortion* bandDistortion = (*iterator);
		//	delete bandDistortion;
		//}
		//*/
		mBandDistortions.front()->ProcessAudio(sampleL, sampleR, &sampleL, &sampleR);

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