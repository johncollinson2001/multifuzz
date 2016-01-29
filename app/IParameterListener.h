#pragma once

class IParameterListener
{
public:
	virtual ~IParameterListener() {}
	virtual void OnParamChange(int parameterIndex, double newValue) = 0;	
};