
#include "Chat.h"

int main() {
	Chat chat;

	chat.reg("user1",  "pass1");
	chat.reg("user2",  "pass5");
	chat.reg("user3",  "pass1");
	chat.reg("user4",  "pass3");
	chat.reg("user5",  "pass3");
	chat.reg("user6",  "pass1");
	chat.reg("user7",  "pass5");
	chat.reg("user8",  "pass6");

	std::cout << " login user1 - pass1 -> " << chat.login("user1", "pass1") << std::endl;
	std::cout << " login user1 - pass2 -> " << chat.login("user1", "pass2") << std::endl;
	std::cout << " login user2 - pass1 -> " << chat.login("user2", "pass1") << std::endl;
	std::cout << " login user3 - pass1 -> " << chat.login("user3", "pass1") << std::endl;
	std::cout << " login user4 - pass1 -> " << chat.login("user4", "pass1") << std::endl;

	chat.del("user3");
	chat.del("user4");

	std::cout << " login user3 - pass1 -> " << chat.login("user3", "pass1") << std::endl;
	std::cout << " login user4 - pass1 -> " << chat.login("user4", "pass1") << std::endl;
	std::cout << " login user7 - pass5 -> " << chat.login("user7", "pass5") << std::endl;
	std::cout << " login user8 - pass0 -> " << chat.login("user8", "pass0") << std::endl;

	return 0;
}