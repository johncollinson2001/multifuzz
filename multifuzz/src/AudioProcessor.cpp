#include "AudioProcessor.h"

// Construct
AudioProcessor::AudioProcessor(Multifuzz* plugin, MultifuzzParameterManager* parameterManager, double sampleRate)
	: mInputGainController(new GainController(parameterManager, "Input Gain", EParameter::InputGain)),
	mOutputGainController(new GainController(parameterManager, "Output Gain", EParameter::OutputGain)),
	mWetDryController(new WetDryController(parameterManager, "Master Wet/Dry", EParameter::MasterWetDry))
{
	// Create band distortion units
	mBandDistortions[0] = new BandDistortion(
		parameterManager,
		"Band One",
		sampleRate,
		{
			EParameter::BandOneBypass,
			EParameter::BandOneDistortionType,
			EParameter::BandOneOverdrive,
			EParameter::BandOneFrequency,
			EParameter::BandOneWidth,
			EParameter::BandOneResonance,
			EParameter::BandOneGain
		});

	mBandDistortions[1] = new BandDistortion(
		parameterManager,
		"Band Two",
		sampleRate,
		{
			EParameter::BandTwoBypass,
			EParameter::BandTwoDistortionType,
			EParameter::BandTwoOverdrive,
			EParameter::BandTwoFrequency,
			EParameter::BandTwoWidth,
			EParameter::BandTwoResonance,
			EParameter::BandTwoGain
		});

	mBandDistortions[2] = new BandDistortion(
		parameterManager,
		"Band Three",
		sampleRate,
		{
			EParameter::BandThreeBypass,
			EParameter::BandThreeDistortionType,
			EParameter::BandThreeOverdrive,
			EParameter::BandThreeFrequency,
			EParameter::BandThreeWidth,
			EParameter::BandThreeResonance,
			EParameter::BandThreeGain
		});

	// Initialise the parameters
	InitialiseParameters();

	// Register parameters with the parameter manager
	parameterManager->RegisterParameterListener(this, &mParameters);
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
		// If by pass, set the outputs to the inputs
		if (mBypass)
		{
			*outL = *inL;
			*outR = *inR;
		}
		else
		{
			double dryL = *inL;
			double dryR = *inR;

			// Process input gain and capture peaks
			mInputGainController->ProcessAudio(dryL, dryR, &dryL, &dryR);
			inPeakL = IPMAX(inPeakL, fabs(dryL));
			inPeakR = IPMAX(inPeakR, fabs(dryR));

			// Process band distortions
			double wetL, wetR;
			ProcessBandDistortions(dryL, dryR, &wetL, &wetR);

			// Process wet/dry
			double mixedL, mixedR;
			mWetDryController->ProcessAudio(dryL, dryR, wetL, wetR, &mixedL, &mixedR);

			// Process output gain and capture peaks
			mOutputGainController->ProcessAudio(mixedL, mixedR, &mixedL, &mixedR);
			outPeakL = IPMAX(outPeakL, fabs(mixedL));
			outPeakR = IPMAX(outPeakR, fabs(mixedR));

			// Assign the sample to the output
			*outL = mixedL;
			*outR = mixedR;
		}
	}

	// Send peak change notification
	SendPeakChangeNotification(inPeakL, inPeakR, outPeakL, outPeakR);
}

// Register a peak change listener with this processor
void AudioProcessor::RegisterPeakListener(IPeakListener* listener)
{
	mPeakListeners.push_back(listener);
}

// Handle parameter changes
void AudioProcessor::ReceiveParameterChangeNotification(int parameterIndex, double newValue)
{
	if (parameterIndex == EParameter::MasterBypass)
	{
		mBypass = newValue;
	}
}

void AudioProcessor::InitialiseParameters()
{
	// Bypass
	Parameter bypass;
	bypass.Id = EParameter::MasterBypass;
	bypass.Name = "Master Bypass";
	bypass.DefaultValue = 1;
	bypass.Type = EParameterType::Bool;
	mParameters.push_back(bypass);
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