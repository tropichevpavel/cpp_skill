#pragma once

#include "IElectronic.h"

class Device : virtual public IElectronic {

	int _weight;

public:
	Device(const int& weight);
	void showSpec() override;
};

class WashMachine final : public Device {

	int _programCount;

public:
	WashMachine(const int& weight, const int& progCount); 
	void showSpec() override;
};
