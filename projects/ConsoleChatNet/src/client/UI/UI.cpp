
#include "UI.h"

UI::UI(App* app) : app(app) {}

void UI::start() {
	do drawPage();
	while (!(isQuit && quit()));
	
	drawPage(-1);
}

void UI::drawPage() {
	clear();
	auto user = app->getUser();

	std::cout << std::endl << "          ~~~CONSOLE CHAT~~~         " << (user ? "SysID: " + std::to_string(user->getID()) : "") << std::endl
						   << "                                     " << (user ? "Name:  " + user->getName() : "") << std::endl;

	int page = getCurrntPage();

	if (page == -1) showByePage();
	else if (page == 0) showStartPage();
	else if (page == 1) showLoginPage();
	else if (page == 2) showRegisterPage();
	else if (page == 3) showChatsPage();
	else if (page == 4) showChatPageNew();
	else if (page == 5) showChatPage();
}

void UI::drawPage(const int page) {
	pushPage(page);
	drawPage();
}

auto UI::getCurrntPage() const -> int {
	return pageStack[pageStack.size() - 1].getPage();
}

PageState& UI::getCurrentPageState() {
	return pageStack[pageStack.size() - 1];
}

void UI::setCurrntPage(const int page) {
	pageStack[pageStack.size() - 1] = PageState(page);
}

void UI::pushPage(const int page) {
	pageStack.push_back(page);
}

void UI::pushPage(const int page, initParams state) {
	pageStack.push_back({ page, state });
}

void UI::back()
{
	pageStack.pop_back();
}

void UI::clear()
{
	std::cout << u8"\e[1;1H\e[2J";
}
