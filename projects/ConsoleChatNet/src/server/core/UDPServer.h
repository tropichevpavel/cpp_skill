#pragma once

#include <iostream>
#include <vector>
#include <arpa/inet.h>

#ifndef PORT
#define PORT 65000
#endif

#ifndef BUFLEN
#define BUFLEN 4096
#endif


class Server
{
	int socket_descr = -1;

public:
	Server() = default;
	~Server();

	bool init();
	void listen();

private:
	void send(const sockaddr_in& client, const std::string& text);
};
