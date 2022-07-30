
#include "../UI.h"

void UI::showChatPageNew() {
	PageState& ps = getCurrentPageState();
	ps.initState({{ "userIDto", 0}});

	int& userIDto = ps.get<int>("userIDto");

	std::cout << "      CHAT :: " << (userIDto ? app->getUserName(userIDto) : "NEW") << std::endl << std::endl;

	auto self = app->getUser();
	auto users = app->getUsers();

	if (!userIDto) {
		if (users.size() < 2)
			std::cout << "There are no more users except you..." << std::endl
					  << "Invite someone!" << std::endl;
		else {
			std::cout << "Select user for start chating!" << std::endl << std::endl;

			for (const auto& user : users)
				if (self != user)
					std::cout << user->getID() << ". "
							  << user->getLogin() << " ("
							  << user->getName() << ")" << std::endl << std::endl;
		}

	} else {
		std::cout << "Say Hi!" << std::endl << std::endl
				  << "Enter first message:" << std::endl;
	}

	drawMenu({{ "", [&](const std::string& input) {
		if (!userIDto) {
			int in = 0;

			try { in = std::stoi(input); } catch (...) { return; }

			for (const auto& user : users)
				if (user->getID() == in) {
					userIDto = in;
					return;
				}
		} else {
			back();
			pushPage(5, {{ "chatID", app->addChat(userIDto, input)}});
		}
	}}});
}

void UI::showChatPage() {
	PageState& ps = getCurrentPageState();
	ps.initState({
		{ "chatID", 0 },
		{ "page", 1 }
	});

	int& chatID = ps.get<int>("chatID");

	auto user = app->getUser();
	auto userID = user->getID();
	auto chat = app->getChat(chatID);
	auto userIDto = !chatID ? -1 : chat->getUserID(userID);

	std::cout << "      CHAT :: " << (!chatID ? "General Сhat" : app->getUserName(userIDto)) << std::endl << std::endl;

	auto& messages = chat->getMessages();

	for (const auto& message : messages) {
		const auto& userIDfrom = message->getUserIDfrom();
		if (userID == userIDfrom)
			std::cout << "                <- ";
		else {
			if (!chatID && userIDto != userIDfrom) {
				userIDto = userIDfrom;
				std::cout << std::endl << " -- " << app->getUserName(userIDto) << ":" << std::endl;
			}

			std::cout << " -> ";
		}

		std::cout << message->getText() << std::endl;
	}

	std::cout << std::endl << "to send message insert text (more 3 char) and press Enter key" << std::endl;

	drawMenu({
		// { "u. PageUp", []() {}},
		// { "d. PageDown", []() {}},
		{ "", [&](const std::string& input) {
			if (input.length() > 3)
				!chatID ? chat->addMessage(userID, input) : chat->addMessage(userID, userIDto, input);
		}
	}});
}
