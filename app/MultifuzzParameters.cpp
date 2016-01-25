#include "MultifuzzParameters.h"

#include <list>
#include "Parameter.h"

using namespace std;

// Construct
MultifuzzParameters::MultifuzzParameters(Multifuzz* plugin) :
	mPlugin(plugin) {
	InitialiseParameters();
}

// Destruct
MultifuzzParameters::~MultifuzzParameters() { }

// Returns the member collection of parameters
list<Parameter>* MultifuzzParameters::GetParameters() {
	return &mParameters;
}

// Initialises the parameters into the member collection
void MultifuzzParameters::InitialiseParameters() {
	// Input Gain
	Parameter inputGain;
	inputGain.Id = EParameters::InputGain;
	inputGain.Name = "Input Gain";
	inputGain.DefaultValue = 0.0;
	inputGain.MinValue = -48.0;
	inputGain.MaxValue = 10.0;
	inputGain.Step = 0.01;
	inputGain.Label = "db";
	inputGain.Group = "";
	inputGain.Shape = 1.0; // TODO: Change accordingly
	mParameters.push_back(inputGain);

	// Output Gainc++
	Parameter outputGain;
	outputGain.Id = EParameters::OutputGain;
	outputGain.Name = "Output Gain";
	outputGain.DefaultValue = 0.0;
	outputGain.MinValue = -48.0;
	outputGain.MaxValue = 10.0;
	outputGain.Step = 0.01;
	outputGain.Label = "db";
	outputGain.Group = "";
	outputGain.Shape = 1.0; // TODO: Change accordingly
	mParameters.push_back(outputGain);

	// Overdrive
	Parameter overdrive;
	overdrive.Id = EParameters::Overdrive;
	overdrive.Name = "Overdrive";
	overdrive.DefaultValue = 100.0;
	overdrive.MinValue = 0.01;
	overdrive.MaxValue = 100.0;
	overdrive.Step = 0.01;
	overdrive.Label = "%";
	overdrive.Group = "";
	overdrive.Shape = 1.0;
	mParameters.push_back(overdrive);
}