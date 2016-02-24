#pragma once

#include <string>
#include "enums\EParameter.h"
#include "enums\EParameterType.h"

using namespace std;

struct Parameter {
	EParameter Id;
	string Name;
	double DefaultValue;
	double MinValue;
	double MaxValue;
	double Step;
	string Label;
	string Group;
	double Shape;
	EParameterType Type;
};