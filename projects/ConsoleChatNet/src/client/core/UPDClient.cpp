
// #include <iostream>
// #include <string>
// #include <arpa/inet.h>
// #include <sys/socket.h>
#include <unistd.h>

#include <functional>

#include <thread>
#include <chrono>

#include "UDPClient.h"

bool Client::init(const std::string& ip, const u_int16_t port)
{
	server.sin_addr.s_addr = inet_addr(ip.c_str());
	server.sin_port = htons(port);
	server.sin_family = AF_INET;

	socket_descr = socket(AF_INET, SOCK_DGRAM, 0);

	if (connect(socket_descr, (sockaddr*) &server, sizeof(server)) < 0)
	{
		std::cout << "Error connect to server " << ip << ":" << port << std::endl;
		exit(1);
	}

	return true;
}

bool Client::auth(const std::string& login, const std::string& pass, User*& user)
{
	if (!send("0 " + std::to_string(LOGIN) + " " + login + " " + pass)) return false;

	std::string response;
	if (!receive(response)) return false;
	ServerResponse sresp(response);

	int user_id = 0;

	try
	{
		user_id = std::stoi(sresp.next_part(true));
	}
	catch(...)
	{
		std::cout << "Error while pars server response" << std::endl;
		return false;
	}

	return user = new User(user_id, login, "", sresp.next_part());
}

bool Client::add_users(const std::string& login, const std::string& pass, const std::string& name)
{
	if (!send("0 " + std::to_string(REGISTER) + " " + login + " " + pass + " " + name)) return false;
	std::string response;
	return receive(response);
}

void Client::get_users(const int& user_id, std::vector<User*>* users)
{
	if (!send(std::to_string(user_id) + " " + std::to_string(GET_USERS)))
	{
		std::cout << "Critical error! cant send data from server! restart plz" << std::endl;
		return;
	}

	std::string response;
	if (!receive(response) && user_id)
	{
		std::cout << "Critical error! cant get data from server! restart plz" << std::endl;
		return;
	}

	int pos_line = 0, pos_eol = 0;

	while ((pos_eol = response.find_first_of('\n', pos_eol)) > 0)
	{
		ServerResponse sresp(response.substr(pos_line, pos_eol - pos_line));
		pos_line = ++pos_eol;

		int user_id = 0;

		try
		{
			user_id = std::stoi(sresp.next_part(true));	
		}
		catch(...)
		{
			std::cout << "Critical error! Error while parse user from server! restart plz" << std::endl;
			exit(1);
		}

		users->push_back(new User(user_id, sresp.next_part(), "", sresp.next_part()));
	}
}

bool Client::add_msg(const int& chat_id, const int& user_id, const int& user_id_to, const std::string& text)
{
	bool status = send(std::to_string(user_id) + " " + std::to_string(SEND) + " " + std::to_string(chat_id) + " " + std::to_string(user_id_to) + " " + text);

	if (status)
	{
		std::string response;
		receive(response);
	}

	return status;
}

void Client::get_msgs(const int& user_id, std::function<void(const int& id, const int& userIDfrom, const int& userIDto, const std::string& text)>& cb)
{
	if (!send(std::to_string(user_id) + " " + std::to_string(GET_MESSAGES))) return;

	std::string response;
	if (!receive(response)) return;

	int pos_line = 0, pos_eol = 0;

	while ((pos_eol = response.find_first_of('\n', pos_eol)) > 0)
	{
		ServerResponse sresp(response.substr(pos_line, pos_eol - pos_line));
		pos_line = ++pos_eol;

		int chat_id = 0,
			user_id = 0,
			user_id_to = 0;

		try
		{
			std::string first = sresp.next_part(true);
			chat_id = std::stoi(first.substr(first[0] == '\U00000001' ? 1 : 0));
			user_id = std::stoi(sresp.next_part());
			user_id_to = std::stoi(sresp.next_part());
		}
		catch(...)
		{
			std::cout << "Error while parse messages from server! restart plz" << std::endl;
			exit(1);
		}

		cb(chat_id, user_id, user_id_to, sresp.last_part());
	}
}

auto Client::get_chat_id_last(const int& user_id) -> int
{
	if (!send(std::to_string(user_id) + " " + std::to_string(GET_CHAT_ID_LAST))) return -1;

	std::string answer;
	if (!receive(answer)) return -1;

	int chat_id = -1;
	try
	{
		chat_id = std::stoi(answer);
	}
	catch(...) {}

	return chat_id;
}

bool Client::send(const std::string& data)
{
	if (sendto(socket_descr, data.c_str(), data.length(), 0, nullptr, sizeof(server)) < 0)
	{
		std::cout << "Critical error!" << strerror(errno) << "! Cant send data from server! restart plz" << std::endl;
		return false;
	}
	return true;
}

bool Client::receive(std::string& data)
{
	char buf[BUFLEN] = {};

	while (data.length() < 2)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		recvfrom(socket_descr, buf, BUFLEN, 0, nullptr, nullptr);

		if (buf[0] == '-') return false;

		data += buf;

		if (data.length() < 2) std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

Client::~Client(){ if (socket_descr != -1) close(socket_descr); }
