
#include <string>
#include <iostream>

#include "MobileDevice.h"

MobileDevice::MobileDevice(const int& weight, const int& sar, const int& batteryCapacity) : Device(weight), Mobile(sar), _batteryCapacity(batteryCapacity) {}

void MobileDevice::showSpec() {
	Device::showSpec();
	Mobile::showSpec();
	std::cout << "Battery Capacity: " << _batteryCapacity << std::endl;
}

Android::Android(const int& weight, const int& sar, const int& batteryCapacity, const int& androidVersion) :
			MobileDevice(weight, sar, batteryCapacity),
			_androidVersion(androidVersion) {}

void Android::showSpec() {
	MobileDevice::showSpec();
	std::cout << "Android Version: " << std::endl;
}

LinuxOS::LinuxOS(const int& weight, const int& sar, const int& batteryCapacity, const std::string& linuxVersion) :
			MobileDevice(weight, sar, batteryCapacity),
			_linuxVersion(linuxVersion) {}

void LinuxOS::showSpec() {
	MobileDevice::showSpec();
	std::cout << "LinuxOS Version: " << std::endl;
}
