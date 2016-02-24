#pragma once

class IParameterListener
{
public:
	virtual ~IParameterListener() {}
	virtual void ReceiveParameterChangeNotification(int parameterIndex, double newValue) = 0;	
};