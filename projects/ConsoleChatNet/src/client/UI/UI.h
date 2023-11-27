#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <initializer_list>
#include <limits>

#include "../App.h"
#include "../core/PageState.h"
#include "Menu.h"

typedef std::initializer_list<std::pair<std::string, AnyData>> initParams;

struct UI
{
	UI(App* app);

	void start();

	void drawPage();
	void drawPage(const int page);
	void drawMenu(Menu options = {});

	auto getCurrntPage() const -> int;
	PageState &getCurrentPageState();
	void setCurrntPage(const int page);
	void pushPage(const int page);
	void pushPage(const int page, initParams state);
	void back();

	void showStartPage();
	void showRegisterPage();
	void showLoginPage();
	void showChatsPage();
	void showChatPageNew();
	void showChatPage();

	void drawChatMessagesGeneral(Chat);
	void drawChatMessagesPM();

	static void showByePage();

	bool quit();
	static void clear();

	template <typename T>
	static void cin(std::function<void(const T&)> cb) {
		T cin;

		std::cin >> cin;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cb(cin);
	}

	static void cin(std::function<void(const std::string&)> cb)
	{
		std::string cin;

		// std::cin.clear();
		// std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::getline(std::cin, cin);

		cb(cin);
	}

private:
	bool isQuit = false;
	std::vector<PageState> pageStack = { PageState(0) };

	App* app;
};
