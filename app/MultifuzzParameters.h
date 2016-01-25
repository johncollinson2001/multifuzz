#pragma once

#include <list>
#include "Multifuzz.h"
#include "Parameter.h"

// Forward declarations
class Multifuzz;

using namespace std;

class MultifuzzParameters
{
public:
	MultifuzzParameters(Multifuzz* plugin);
	~MultifuzzParameters();
	list<Parameter>* GetParameters();

private:
	Multifuzz* mPlugin;
	list<Parameter> mParameters = list<Parameter>();
	void InitialiseParameters();
};

