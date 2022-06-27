
#include <tuple>

#include "UI.h"
#include "Menu.h"

void UI::drawMenu(Menu options) {
	int curPage = getCurrntPage();
	if (curPage > 0) {
		if (curPage == 3 && app->isLogin())
			options["l. LogOut"] = [this]() { app->logout(); back(); };
		else
			options["b. Back"] = [this]() { back(); };
	}
	options["q. Quit"] = [this]() { isQuit = true; drawPage(); };

	std::cout << std::endl;

	for (const auto& option : options)
		if (!option->key.empty())
			std::cout << option->key << " | ";

	std::cout << std::endl << std::endl;

	if (isQuit) return;

	if (!options.has(""))
		cin<char>([&](const char& input) {
			for (const auto& option : options)
				if (option->key[0] == input) {
					std::get<singleOption>(option->function)();
					return;
				}
		});

	else
		cin([&](const std::string& input) {
			if (!input.empty()) {
				if (input.length() == 1)
					for (const auto& option : options)
						if (option->key[0] == input[0]) {
							std::get<singleOption>(option->function)();
							return;
						}
				std::get<multiOption>(options[""].function)(input);
			}
		});
}

bool UI::quit() {
	std::cout << "Are you sure? (y/n) ";
	bool isQuit = false;

	cin<char>([&](const char& input) mutable {
		this->isQuit = input != 'n';
		isQuit = input == 'y';
	});

	return isQuit;
}
