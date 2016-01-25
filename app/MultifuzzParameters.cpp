#include "MultifuzzParameters.h"

#include <list>
#include "Parameter.h"

using namespace std;

MultifuzzParameters::MultifuzzParameters(Multifuzz* plugin) :
	mPlugin(plugin) {
	InitialiseParameters();
}

// Returns the member collection of parameters
list<Parameter>* MultifuzzParameters::GetParameters() {
	return &mParameters;
}

// Initialises the parameters into the member collection
void MultifuzzParameters::InitialiseParameters() {
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