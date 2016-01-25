#pragma once

#include <list>
#include "Multifuzz.h"
#include "Preset.h"

// Forward declarations
class Multifuzz;

using namespace std;

class MultifuzzPresets
{
public:
	static const int NumberOfPresets = 5;

	MultifuzzPresets(Multifuzz* plugin);
	list<Preset>* GetPresets();

private:
	Multifuzz* mPlugin;
	list<Preset> mPresets = list<Preset>();
	void InitialisePresets();
};

