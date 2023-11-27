
#include "../UI.h"

void UI::showStartPage() {
	std::cout << "      StartPage" << std::endl << std::endl
			  << "Our chat greetings you!" << std::endl
			  << "Choose one option to start use this beautifull chat!" << std::endl;

	this->drawMenu({
		{ "1. Login",	 [&]() { this->pushPage(1); }},
		{ "2. Register", [&]() { this->pushPage(2); }}
	});
}
