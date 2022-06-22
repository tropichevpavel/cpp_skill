
#include <iostream>

#include "Device.h"

Device::Device(const int& weight) : _weight(weight) {}

void Device::showSpec() {
	std::cout << "Weight: " << _weight << " g." << std::endl;
}

WashMachine::WashMachine(const int& weight, const int& progCount) : Device(weight), _programCount(progCount) {}

void WashMachine::showSpec() {
	std::cout << "Wash programs: " << _programCount << std::endl;
	Device::showSpec();
}
