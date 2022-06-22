
#include "SnackSlot.h"

SnackSlot::SnackSlot(const int& s) : size(s) {}

void SnackSlot::setSnack(Snack* snack) {
	this->snack = snack;
}

void SnackSlot::loadSnack(const int& count) {
	this->snackCount = (this->snackCount + count) > this->size ? this->size : (this->snackCount + count);
}

int SnackSlot::getSnackCount() {
	return this->snackCount;
}

bool SnackSlot::popSnack() {
	return this->snackCount >= 0 ? this->snackCount-- : false;
}

void SnackSlot::printSnackInfo() {
	std::cout << *(this->snack);
}

// double& SnackSlot::getSnackWeight() {
// 	return this->snack->getWeight();
// }

double& SnackSlot::getSnackPrice() {
	return this->snack->getPrice();
}

SnackSlot::~SnackSlot() {
	delete this->snack;
}
