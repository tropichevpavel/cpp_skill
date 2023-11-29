#pragma once

#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include "Logger.h"

#ifndef PORT
#define PORT 65000
#endif

#ifndef BUFLEN
#define BUFLEN 4096
#endif

constexpr std::string_view logger_file = "./log.txt";

class Server
{
	int socket_descr = -1;
	Logger* logger;

	enum
	{
		LOGIN,
		REGISTER,
		GET_USERS,
		GET_MESSAGES,
		SEND,
		GET_CHAT_ID_LAST
	};

public:
	Server() = default;
	~Server();

	bool init();
	void listen();

private:
	void send(const sockaddr_in& client, const std::string& text);
	auto parse(const std::string& buffer, std::string& answer) -> std::string&;
};
