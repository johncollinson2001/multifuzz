#include "MultifuzzPresets.h"

#include <list>
#include "Preset.h"

using namespace std;

// Construct
MultifuzzPresets::MultifuzzPresets(Multifuzz* plugin) :
	mPlugin(plugin) {
	InitialisePresets();	
}

// Returns the private collection of presets
list<Preset>* MultifuzzPresets::GetPresets() {
	return &mPresets;
}

// Initialises the presets into the member collection
void MultifuzzPresets::InitialisePresets() {
	// Clean
	Preset clean;
	clean.Name = "Clean";
	clean.Overdrive = 100.0;
	mPresets.push_back(clean);

	// Slightly distorted
	Preset slightlyDistorted;
	slightlyDistorted.Name = "Slightly distorted";
	slightlyDistorted.Overdrive = 80.0;
	mPresets.push_back(slightlyDistorted);

	// Woo
	Preset woo;
	woo.Name = "Woo";
	woo.Overdrive = 40.0;
	mPresets.push_back(woo);

	// Waa
	Preset waa;
	waa.Name = "Waa";
	waa.Overdrive = 20.0;
	mPresets.push_back(waa);

	// Buzz
	Preset buzz;
	buzz.Name = "Buzz";
	buzz.Overdrive = 0.01;
	mPresets.push_back(buzz);	
}
