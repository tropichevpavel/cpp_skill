#pragma once
#include <vector>

#include "SnackSlot.h"

class SnackBar {

	double money;
	int slotCount;
	int selectSlot;

	std::vector<SnackSlot*> slots;

public:
	SnackBar();
	SnackBar(const int& count);
	void loadSlot(SnackSlot* slot);
	
	void getSnackList();
	bool selectSnack(const int& slot);

	void insertMoney(const double& count);
	double getMoney();
	
	bool buySnack();

	~SnackBar();
};