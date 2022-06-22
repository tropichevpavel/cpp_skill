
#include <iostream>
#include <limits>

#include "entities/IElectronic.h"
#include "entities/Device.h"
#include "entities/MobileDevice.h"

int main() {

	IElectronic* store[4];

	store[0] = new Android(230, 6, 3000, 9);
	store[1] = new LinuxOS(430, 6, 3000, "CentOS");
	store[2] = new WashMachine(24000, 15);
	store[3] = new Player(1, 8);

	while (true) {
		int choise;
		std::cout << "Welcom to our electronic store!" << std::endl
				  << "Chose prod: " << std::endl << std::endl
				  << "1 - Mobile Android, 2 - Mobile LinuxOS, 3 - Wash Machine, 4 - Player, 0 - exit" << std::endl;

		std::cin >> choise;

		if (choise == 0) break;
		else if (choise == 1 || choise == 2 || choise == 3 || choise == 4) {
			store[choise - 1]->showSpec();
		} else
			std::cout << "Wrong option, choose the right one!" << std::endl;

		std::cout << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "See you soon!" << std::endl;

	for (IElectronic* item : store)
		delete item;

	return 0;
}
