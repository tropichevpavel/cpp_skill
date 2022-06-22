#pragma once

#include <string>

#include "Mobile.h"
#include "Device.h"

class MobileDevice : public Mobile, Device {

	int _batteryCapacity;

public:
	MobileDevice(const int& weight, const int& sar, const int& batteryCapacity);
	void showSpec() override;
};

class Android final : public MobileDevice {
	int _androidVersion;

public:
	Android(const int& weight, const int& sar, const int& batteryCapacity, const int& androidVersion);
	void showSpec() override;
};

class LinuxOS final : public MobileDevice {
	std::string _linuxVersion;

public:
	LinuxOS(const int& weight, const int& sar, const int& batteryCapacity, const std::string& linuxVersion);
	void showSpec() override;
};