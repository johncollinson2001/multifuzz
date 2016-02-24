#pragma once

class IPeakListener
{
public:
	virtual ~IPeakListener() {}
	virtual void ReceivePeakChangeNotification(double inPeakL, double inPeakR, double outPeakL, double outPeakR) = 0;
};
