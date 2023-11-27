#pragma once

#include <iostream>
#include <vector>
#include <arpa/inet.h>

#include "../entities/User.h"

#ifndef IP
#define IP "127.0.0.1"
#endif

#ifndef PORT
#define PORT 65000
#endif

#ifndef BUFLEN
#define BUFLEN 4096
#endif

enum
{
	LOGIN,
	REGISTER,
	GET_USERS,
	GET_MESSAGES,
	SEND,
	GET_CHAT_ID_LAST
}
COMMAND;

class ServerResponse
{
	size_t pos_cur = 0;
	int pos_next = 0;

	std::string data;

public:
	ServerResponse(const std::string& data) : data(data) {};

	auto next_part(const bool& is_new = false, const char delimetr = ' ') -> std::string
	{
		if (is_new)
		{
			pos_cur = 0;
			pos_next = data.find_first_of(delimetr);
		}
		else
		{
			if (pos_next < -1) return "";

			pos_cur = pos_next + 1;
			pos_next = data.find_first_of(delimetr, pos_cur);
		}

		return data.substr(pos_cur, pos_next < 0 ? SIZE_MAX : (pos_next - pos_cur));
	};

	auto last_part() -> std::string
	{
		return data.substr(pos_next + 1);
	};
};

class Client
{
	int socket_descr = -1;
	sockaddr_in server;

public:
	Client() = default;
	~Client();

	bool init(const std::string& ip = IP, const u_int16_t port = PORT);
	bool auth(const std::string& login, const std::string& pass, User*& user);
	bool add_users(const std::string& login, const std::string& pass, const std::string& name);
	void get_users(const int& user_id, std::vector<User*>* users);
	void get_msgs(const int& user_id, std::function<void(const int& id, const int& userIDfrom, const int& userIDto, const std::string& text)>& cb);
	bool add_msg(const int& chat_id, const int& user_id, const int& user_id_to, const std::string& text);
	auto get_chat_id_last(const int& user_id) -> int;

private:
	bool send(const std::string& data);
	bool receive(std::string& data);
};
