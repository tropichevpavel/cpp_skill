#pragma once

#include <functional>
#include <string>
#include <vector>
#include <variant>
#include <initializer_list>

#include "../core/AnyData.h"

typedef std::function<void()> singleOption;
typedef std::function<void(const std::string&)> multiOption;

struct Option {
	std::string key;
	std::variant<singleOption, multiOption, int*> function = nullptr;

	Option(const std::string& key);

	template <typename T>
	Option(const std::string& key, const T& function) : key(key), function(function) {}

	Option(const Option& option) = delete;
	Option(Option&& option);

	template <typename T>
	void operator= (const T& function) {
		this->function = function;
	}
};

typedef std::initializer_list<Option> initOptions;
typedef std::initializer_list<Option*> initOptionsPtr;

class Menu {
	std::vector<Option*> options = {};

public:
	Menu() = default;
	Menu(std::vector<Option*> options);
	Menu(initOptions options);
	Menu(initOptionsPtr options);

	Menu(const Menu& menu) = delete;
	Menu(Menu&& menu) = delete;

	auto begin() const -> std::vector<Option* const>::iterator;
	auto end() const -> std::vector<Option* const>::iterator;

	auto operator[](std::string key) -> Option&;

	auto has(const std::string& key) const -> const bool;

	~Menu();
};
