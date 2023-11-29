
#include "../UI.h"

void UI::showChatsPage()
{
	app->loadState();

	std::cout << "      CHATS" << std::endl << std::endl;

	auto user = app->getUser();
	auto userID = user->getID();
	auto chats = app->getChats(userID);

	if (!chats.size())
		std::cout << "Chat list empty!" << std::endl
				  << "Enjoy chating by add new!" << std::endl;

	else {
		for (int i = 0; i < (int) chats.size(); ++i)
		{
			const auto chat = chats[i];

			auto text = chat->getLastMessage()->getText();

			std::cout << "  " << i
					<< " >> "
					<< (chat->getID() == 0 ? "General Сhat" : app->getUserName(chat->getUserID(userID))) << std::endl
					<< "    ---> "
					<< (text.size() > 20 ? text.substr(0, 17) + "..." : text) << std::endl << std::endl;
		}

		std::cout << "Select Chat or Start New" << std::endl;
	}

	drawMenu(
	{
		{ "", [&](const std::string& input)
				{
					int in = 0;
					try { in = std::stoi(input); } catch (...) { return; }

					auto chat = app->getChat(in);

					if (chat)
					{
						pushPage(5, {{ "chatID", chat->getID() }});
						return;
					}
				}
		},
		{ "n. New", [this]() { pushPage(4); } }
	});
}
