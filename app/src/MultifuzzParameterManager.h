#pragma once

#include <list>
#include <map>
#include "Multifuzz.h"
#include "structs\Parameter.h"
#include "enums\EParameters.h"
#include "interfaces\IParameterListener.h"

// Forward declarations
class Multifuzz;

using namespace std;

class MultifuzzParameterManager
{
public:
	MultifuzzParameterManager(Multifuzz* plugin);
	~MultifuzzParameterManager();
	list<Parameter> GetParameters();
	void SendParameterChangeNotification(int parameterIndex);
	void RegisterParameterListener(IParameterListener* listener, list<Parameter>* parameters);

private:
	Multifuzz* mPlugin;
	map<IParameterListener*, list<Parameter>*> mParameterMap = map<IParameterListener*, list<Parameter>*>();	
};

