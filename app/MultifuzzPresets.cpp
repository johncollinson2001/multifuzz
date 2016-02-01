#include "MultifuzzPresets.h"

#include <list>
#include "Preset.h"
#include "SweetyFuzzPreset.h"
#include "MegaFuzzPreset.h"
#include "FuzzyFuzzPreset.h"
#include "MentalFuzzPreset.h"

using namespace std;

// Construct
MultifuzzPresets::MultifuzzPresets(Multifuzz* plugin) :
	mPlugin(plugin) 
{
	InitialisePresets();	
}

// Returns the private collection of presets
list<Preset>* MultifuzzPresets::GetPresets() 
{
	return &mPresets;
}

// Initialises the presets into the member collection
void MultifuzzPresets::InitialisePresets() 
{
	// Add a default
	Preset defaultPreset;
	defaultPreset.Name = "Default";
	mPresets.push_back(defaultPreset);

	// Add the custom presets defined in their own files
	mPresets.push_back(SweetyFuzzPreset::Get());
	mPresets.push_back(MegaFuzzPreset::Get());
	mPresets.push_back(FuzzyFuzzPreset::Get());
	mPresets.push_back(MentalFuzzPreset::Get());
}
