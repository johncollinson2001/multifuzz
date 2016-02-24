#include "MultifuzzPresets.h"

#include <list>
#include "structs\Preset.h"
#include "presets\DefaultPreset.h"
#include "presets\SweetyFuzzPreset.h"
#include "presets\MegaFuzzPreset.h"
#include "presets\FuzzyFuzzPreset.h"
#include "presets\MentalFuzzPreset.h"

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
	mPresets.push_back(DefaultPreset::Get());
	// Add the custom presets
	mPresets.push_back(SweetyFuzzPreset::Get());
	mPresets.push_back(MegaFuzzPreset::Get());
	mPresets.push_back(FuzzyFuzzPreset::Get());
	mPresets.push_back(MentalFuzzPreset::Get());
}
