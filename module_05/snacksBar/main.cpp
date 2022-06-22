#include <iostream>

#include "entities/SnackBar.h"

SnackBar* loadBar() {
	SnackBar* bar = new SnackBar(10);

	SnackSlot* slot1 = new SnackSlot(5);
	slot1->setSnack(new Snack("Bounty", 280, 3.4));
	slot1->loadSnack(5);
	bar->loadSlot(slot1);

	SnackSlot* slot2 = new SnackSlot(10);
	slot2->setSnack(new Snack("Twix", 310, 5.1));
	slot2->loadSnack(8);
	bar->loadSlot(slot2);

	SnackSlot* slot3 = new SnackSlot(15);
	slot3->setSnack(new Snack("Zebra", 120, 0.5));
	slot3->loadSnack(2);
	bar->loadSlot(slot3);

	return bar;
}

int main () {

	int userChoice = 0;
	auto bar = loadBar();

	while (true) {
		std::cout << "Hello stranger! Do you wonna get a litte snack?" << std::endl
				  << "1. Show me what we got!" << std::endl
				  << "2. Yeh, but firstly get my money!" << std::endl
				  << "0. Exit" << std::endl;

		std::cin >> userChoice;
		std::cout << std::endl;

		if (userChoice == 1) {
			bar->getSnackList();
			std::cout << std::endl << "Chose one, and pay! You got " << bar->getMoney() << " ¥" << std::endl << std::endl;

			std::cin >> userChoice;
			while (!bar->selectSnack(userChoice - 1)) {
				std::cout << "Wrong option, choose the right one!" << std::endl;
				std::cin >> userChoice;
			}
			
			if (bar->buySnack()) std::cout << "Thanks for buy!!!" << std::endl << "Wait for snack out!";
			else std::cout << "Need more money! OR slot empty!";
		
		} else if (userChoice == 2) {
			std::cout << "Ok, enter how much money you put to my money box" << std::endl;
			
			std::cin >> userChoice;
			bar->insertMoney(userChoice);

		} else if (userChoice == 0) {
			if (bar->getMoney())
				std::cout << "You have got " << bar->getMoney() << " ¥ " << " a-a-and i taking it to my personal Fond of Snacks!";
			break;
		} else if (userChoice > 2) std::cout << "I have only 3 options! You see, dont you?";
		else std::cout << "How you can type this? I have only NUMPAD!";

		std::cout << std::endl << std::endl;
	

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	delete bar;
	return 0;
}