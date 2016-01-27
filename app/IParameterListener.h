#pragma once

class IParameterListener
{
public:
	virtual ~IParameterListener() {}
	virtual void OnParamChange(int parameterIndex) = 0;	
};