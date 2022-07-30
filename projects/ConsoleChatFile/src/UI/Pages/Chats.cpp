
#include "../UI.h"

void UI::showChatsPage() {
	std::cout << "      CHATS" << std::endl << std::endl;

	auto user = app->getUser();
	auto userID = user->getID();
	auto chats = app->getChats(userID);

	if (!chats.size())
		std::cout << "Chat list empty!" << std::endl
				  << "Enjoy chating by add new!" << std::endl;

	else {
		for (const auto& chat : chats) {
			auto text = chat->getLastMessage()->getText();

			std::cout << "  " << chat->getID()
					<< " >> "
					<< (chat->getID() == 0 ? "General Сhat" : app->getUserName(chat->getUserID(userID))) << std::endl
					<< "    ---> "
					<< (text.size() > 20 ? text.substr(0, 17) + "..." : text) << std::endl << std::endl;
		}

		std::cout << "Select Chat or Start New" << std::endl;
	}

	drawMenu({
		{ "", [&](const std::string& input) {
			int in = 0;
			try { in = std::stoi(input); } catch (...) { return; }

			for (const auto& chat : chats)
				if (chat->getID() == in) {
					pushPage(5, {{ "chatID", in }});
					return;
				}
		}},
		{ "n. New", [this]() { pushPage(4); } }
	});
}
