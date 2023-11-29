
#include "../UI.h"

void UI::showChatPageNew()
{
	app->loadStateUsers();

	PageState& ps = getCurrentPageState();
	ps.initState({{ "userIDto", -1}});

	int& userIDto = ps.get<int>("userIDto");

	std::cout << "      CHAT :: " << (userIDto ? app->getUserName(userIDto) : "NEW") << std::endl << std::endl;

	auto self = app->getUser();
	std::vector<User*> users;

	for (const auto user : app->getUsers())
	{
		if (self->getID() != user->getID() && !app->checkUserIDInChats(user->getID())) users.push_back(user);
	}

	if (userIDto < 0)
	{
		if (!users.size())
		{
			std::cout << "There are no more users except you... or u have chat with all of them!" << std::endl
					  << "U can invite someone more!" << std::endl;
		}
		else
		{
			std::cout << "Select user for start chating!" << std::endl << std::endl;

			for (const auto& user : users)
			{
				std::cout << user->getID() << ". "
							<< user->getLogin() << " ("
							<< user->getName() << ")" << std::endl << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Say Hi!" << std::endl << std::endl
				  << "Enter first message:" << std::endl;
	}

	drawMenu({{ "", [&](const std::string& input) {
		if (userIDto < 0)
		{
			int in = 0;

			try { in = std::stoi(input); } catch (...) { return; }

			for (const auto& user : users)
			{
				if (user->getID() == in)
				{
					userIDto = in;
					return;
				}
			}
		}
		else
		{
			back();
			pushPage(5, {{ "chatID", app->addChatServer(userIDto ? userIDto : -1, input)}});
		}
	}}});
}

void UI::showChatPage()
{
	app->loadStateMassages();

	PageState& ps = getCurrentPageState();
	ps.initState({
		{ "chatID", 0 },
		{ "page", 1 }
	});

	auto user = app->getUser();
	auto userID = user->getID();
	auto chat = app->getChatByID(ps.get<int>("chatID"));

	const int& chatID = chat->getID();

	auto userIDto = !chatID ? -1 : chat->getUserID(userID);

	std::cout << "      CHAT :: " << (!chatID ? "General Сhat" : app->getUserName(userIDto)) << std::endl << std::endl;

	auto& messages = chat->getMessages();

	for (const auto& message : messages)
	{
		const auto& userIDfrom = message->getUserIDfrom();
		if (userID == userIDfrom)
		{
			std::cout << "                <- ";
		}
		else
		{
			if (!chatID && userIDto != userIDfrom)
			{
				userIDto = userIDfrom;
				std::cout << std::endl << " -- " << app->getUserName(userIDto) << ":" << std::endl;
			}

			std::cout << " -> ";
		}

		std::cout << message->getText() << std::endl;
	}

	std::cout << std::endl << "to send message insert text (more 3 char) and press Enter key" << std::endl;

	drawMenu(
	{
		{ "", [&](const std::string& input)
			{
				if (input.length() > 3) app->addMessageServer(chatID, userID, userIDto, input);
			}
	}});
}
