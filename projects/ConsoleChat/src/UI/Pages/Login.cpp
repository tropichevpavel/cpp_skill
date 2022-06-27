
#include "../UI.h"

void UI::showLoginPage() {
	PageState &ps = this->getCurrentPageState();
	ps.initState({
		{ "login", std::string("") },
		{ "pass",  std::string("") }
	});

	std::cout << "      LOGIN" << std::endl
			  << "Okey, now enter your" << std::endl
			  << "login: ";

	std::string& login = ps.get<std::string>("login");
	std::string& pass  = ps.get<std::string>("pass");

	if (login == "") std::cin >> login;
	else std::cout << login << std::endl;

	std::cout << "pass:  ";
	if (pass == "") std::cin >> pass;
	else std::cout << pass << std::endl;

	if (this->app->auth(login, pass)) {
		this->back();
		this->pushPage(3);
		this->drawPage();
		return;

	} else
		std::cout << "Incorrect login or pass!" << std::endl;

	this->drawMenu({{ "1. Retry", [&]() mutable { login = ""; pass = ""; }}});
}
