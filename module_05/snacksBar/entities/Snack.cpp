#include <iostream>

#include "Snack.h"

Snack::Snack(const std::string& n, const double& w, const double& p) : name(n), weight(w), price(p) {}

double& Snack::getPrice(){
	return this->price;
}

std::ostream& operator<<(std::ostream& out, const Snack& snack) {
	out << snack.name << " - " << snack.weight << " -- " << snack.price << " ¥";
	return out;
}
