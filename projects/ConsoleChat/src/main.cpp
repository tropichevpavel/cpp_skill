
#include "App.h"

int main() {

	App app;

	// ---- TEST DATA ---- //

	app.initUsers({
		new User(1, "test", "ttt", "Testov T."),
		new User(2, "alex165", "aaa", "Alex E."),
		new User(3, "mart555ee", "mmm", "Marta Luck"),
		new User(4, "dup123ww", "ddd", "Evgen S."),
		new User(5, "nagibator3000", "nnn", "Danay M.")
	});

	auto chat0 = new Chat(0, 1, "hi all!");
	chat0->addMessage(1, "yep! my first mess!");
	chat0->addMessage(2, "greetings all!");
	chat0->addMessage(2, "and i`m second");
	chat0->addMessage(3, "third");
	chat0->addMessage(4, "fourth");
	chat0->addMessage(4, "who next?");
	chat0->addMessage(5, "me!");
	chat0->addMessage(5, "fifth!!!");

	auto chat1 = new Chat(1, 2, 1, "Hi!");
	chat1->addMessage(1, 2, "Hello!");
	chat1->addMessage(2, 1, "How are you?");
	chat1->addMessage(2, 1, "How do u do wat u do?");
	chat1->addMessage(1, 2, "Nomal");
	chat1->addMessage(1, 2, "What does it mean?");
	chat1->addMessage(1, 2, "and u?");

	auto chat2 = new Chat(2, 3, 1, "Hi!");
	chat2->addMessage(1, 3, "Hello!");
	chat2->addMessage(3, 1, "How are you?");
	chat2->addMessage(3, 1, "How do u do wat u do?");
	chat2->addMessage(1, 3, "Nomal");
	chat2->addMessage(1, 3, "What does it mean?");
	chat2->addMessage(1, 3, "and u?");

	auto chat3 = new Chat(3, 5, 1, "Hi!");
	chat3->addMessage(1, 5, "Hello!");
	chat3->addMessage(5, 1, "How are you?");
	chat3->addMessage(5, 1, "How do u do wat u do?");
	chat3->addMessage(1, 5, "Nomal");
	chat3->addMessage(1, 5, "What does it mean?");
	chat3->addMessage(1, 5, "and u? loooooooooongggggggg");

	app.initChats({
		chat0,
		chat1,
		chat2,
		chat3
	});

	// ---- TEST DATA ---- //

	app.start();

	return 0;
}
