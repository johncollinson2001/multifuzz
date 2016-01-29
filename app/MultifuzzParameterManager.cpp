#include "MultifuzzParameterManager.h"

#include <list>
#include "Parameter.h"

using namespace std;

// Construct
MultifuzzParameterManager::MultifuzzParameterManager(Multifuzz* plugin) :
	mPlugin(plugin) { }

// Destruct
MultifuzzParameterManager::~MultifuzzParameterManager() { }

// Return a list of the parameters that have been registered by the parameter listeners
list<Parameter> MultifuzzParameterManager::GetParameters() {
	list<Parameter> result = list<Parameter>();

	// Iterate over the parameter map and add the list of parameters for each
	// listener to the result
	typedef map<IParameterListener*, list<Parameter>*>::iterator iteratorType;
	for (
		iteratorType iterator = mParameterMap.begin(); 
		iterator != mParameterMap.end(); 
		iterator++) {

		result.insert(result.end(), iterator->second->begin(), iterator->second->end());		
	}

	//// Overdrive
	//// TODO: Remove into it's own dsp class
	//Parameter overdrive;
	//overdrive.Id = EParameters::Overdrive;
	//overdrive.Name = "Overdrive";
	//overdrive.DefaultValue = 100.0;
	//overdrive.MinValue = 0.01;
	//overdrive.MaxValue = 100.0;
	//overdrive.Step = 0.01;
	//overdrive.Label = "%";
	//overdrive.Group = "";
	//overdrive.Shape = 1.0;
	//result.push_back(overdrive);

	return result;
}

// Registers a parameter listener with this class
void MultifuzzParameterManager::RegisterParameterListener(IParameterListener* listener, list<Parameter>* parameters) {
	mParameterMap[listener] = parameters;
}

// Handles a parameter change
void MultifuzzParameterManager::OnParamChange(int parameterIndex) {
	// Iterate over the listeners in the map
	for (map<IParameterListener*, list<Parameter>*>::iterator mapIterator = mParameterMap.begin();
		mapIterator != mParameterMap.end();
		mapIterator++) {
		IParameterListener* listener = mapIterator->first;
		list<Parameter>* parameters = mapIterator->second;

		// Iterate over the parameters that the listener is handling
		for (list<Parameter>::iterator paramIterator = parameters->begin();
			paramIterator != parameters->end();
			paramIterator++) {
			// If the listener is interested in this parameter index, then call the listener
			Parameter parameter = (*paramIterator);
			if (parameter.Id == parameterIndex) {
				listener->OnParamChange(parameterIndex);
			}
		}
	}
}