
#include <iostream>

#include "Mobile.h"

Mobile::Mobile(const int& sar) : _sar(sar) {}

void Mobile::showSpec() {
	std::cout << "SAR: " << _sar << " Wt/kg" << std::endl;
}

Player::Player(const int& sar, const int& memoryCount) : Mobile(sar), _memoryCount(memoryCount) {}

void Player::showSpec() {
	Mobile::showSpec();
	std::cout << "Memory: " << _memoryCount << " Gb" << std::endl;
}
