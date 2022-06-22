
#include "SnackBar.h"

SnackBar::SnackBar(const int& count) : slotCount(count) {}

void SnackBar::loadSlot(SnackSlot* slot) {
	if (this->slots.size() < this->slotCount)
		this->slots.push_back(slot);
	else
		std::cout << "Look like no empty slots... find another bar!" << std::endl;
}

void SnackBar::getSnackList() {

	if (this->slots.empty()) {
		std::cout << "Look like no slots... find another bar!" << std::endl;
		return;
	}

	int i = 1;
	for (SnackSlot* slot : this->slots) {
		std::cout << i++ << ". ";
		slot->printSnackInfo();
		std::cout << std::endl;
	}
}

bool SnackBar::selectSnack(const int& slot) {
	if (this->slots.size() < slot) return false;

	this->selectSlot = slot;
	return true;
}

double SnackBar::getMoney() {
	return this->money;
}

void SnackBar::insertMoney(const double& money) {
	this->money += money;
}

bool SnackBar::buySnack() {
	const double& snackPrice = (*this->slots[selectSlot]).getSnackPrice();

	return (this->money - snackPrice >= 0 && (*this->slots[selectSlot]).popSnack()) ? (this->money -= snackPrice) : false;
}

SnackBar::~SnackBar() {
	for (SnackSlot* slot : this->slots)
		delete slot;
}
