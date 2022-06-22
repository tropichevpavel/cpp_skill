#include <iostream>
#include "Human.h"
#include "Human.h"

using namespace humans;

double expon(const double& a, const double& b) {
	return b == 1 ? a : (a * expon(a, b - 1));
}

double imt(Human h) {
	return (h.weight/2.205) / expon((h.height/39.37), 2);
}

int main() {

	// Human human1 = {"P", "A", 12, 21, 45};
	// Human human2{"A", "P", 31, 65, 55};

	Human human3;
	human3.name = "D";
	human3.sur = "Sur";
	human3.height = 140;
	human3.weight = 40;
	human3.setAge(-30);

	Human *h4 = new Human(-30);
	// h4->age = 4;

	std::cout << h4->getAge() << std::endl;

	delete h4;

	std::cout << HumanAge::YANG << std::endl;

	return 0;
}