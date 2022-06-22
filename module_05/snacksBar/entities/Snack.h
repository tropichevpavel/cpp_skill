#pragma once
#include <iostream>

class Snack {

	std::string name;
	double price;
	double weight;
	
	public:
	Snack(const std::string& name, const double& weight, const double& price);

	double& getPrice();

	friend std::ostream& operator<<(std::ostream& out, const Snack& snack);
};
