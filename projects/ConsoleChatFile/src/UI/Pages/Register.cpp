
#include "../UI.h"

void UI::showRegisterPage() {

	PageState &ps = this->getCurrentPageState();
	ps.initState({
		{ "login", std::string("") },
		{ "pass",  std::string("") },
		{ "name",  std::string("") }
	});

	std::cout << "      REGISTER" << std::endl
			  << "For begin enter you" << std::endl
			  << "login: ";

	std::string& login = ps.get<std::string>("login");
	std::string& pass  = ps.get<std::string>("pass");
	std::string& name  = ps.get<std::string>("name");

	if (login == "") std::cin >> login;
	else std::cout << login << std::endl;

	if (this->app->checkUserLogin(login))
		std::cout << "Login is busy!";

	else {
		std::cout << "pass:  ";
		if (pass == "") std::cin >> pass;
		else std::cout << pass << std::endl;

		std::cout << "name:  ";
		if (name == "") std::cin >> name;
		else std::cout << name << std::endl;
	}

	if (login != "" && pass != "" && name != "") {
		this->app->addUser(login, pass, name);

		this->back();
		this->drawPage();
		return;
	}

	this->drawMenu({{ "1. Retry", [&]() mutable { login = ""; }}});
}
