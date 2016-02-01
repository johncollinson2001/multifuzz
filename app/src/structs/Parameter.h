#pragma once

#include <string>
#include "enums\EParameters.h"

using namespace std;

struct Parameter {
	EParameters Id;
	string Name;
	double DefaultValue;
	double MinValue;
	double MaxValue;
	double Step;
	string Label;
	string Group;
	double Shape;
};