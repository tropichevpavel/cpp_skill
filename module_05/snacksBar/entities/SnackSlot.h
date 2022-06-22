#pragma once

#include "Snack.h"

class SnackSlot {

	int size;

	Snack* snack;
	int snackCount;

	public:
	SnackSlot(const int& size);

	int getSnackCount();
	bool popSnack();
	void setSnack(Snack* snack);
	void loadSnack(const int& count);

	double& getSnackPrice();

	void printSnackInfo();

	~SnackSlot();
};