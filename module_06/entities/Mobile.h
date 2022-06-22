#pragma once

#include "IElectronic.h"

class Mobile : virtual public IElectronic {

	int _sar;

public:
	Mobile(const int& sar);
	void showSpec() override;
};

class Player final :  public Mobile {

	int _memoryCount;

public:
	Player(const int& sar, const int& memoryCount);
	void showSpec() override;
};
