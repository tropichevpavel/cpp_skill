
#include "Menu.h"

Option::Option(const std::string& key) : key(key) {}

Option::Option(Option&& option) : key(option.key), function(option.function) {
	option.function = nullptr;
};

Menu::Menu(std::vector<Option*>& options) : options(options) {}

Menu::Menu(initOptions options) {
	for (const auto& option : options)
		this->options.push_back(new Option(std::move(const_cast<Option&>(option))));
}

Menu::Menu(initOptionsPtr options) {
	for (const auto& option : options)
		this->options.push_back(option);
}

auto Menu::begin() -> std::vector<Option*>::iterator {
	return options.begin();
}
auto Menu::end() -> std::vector<Option*>::iterator {
	return options.end();
}

auto Menu::operator[](std::string key) -> Option& {
	for (auto option : options)
		if (option->key == key)
			return *option;

	options.push_back(new Option(key));
	return *(options[options.size() - 1]);
}

auto Menu::has(const std::string& key) const -> bool {
	for (const auto& option : options)
		if (option->key == key)
			return true;

	return false;
}

Menu::~Menu() {
	for (auto option : options) delete option;
}
