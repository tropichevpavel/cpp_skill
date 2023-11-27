#include <unistd.h>

#include "UDPServer.h"
#include "Logic.h"

#include "DBWrapper.h"

bool Server::init()
{
	if (socket_descr != -1) return false;

	socket_descr = socket(AF_INET, SOCK_DGRAM, 0);

	if (socket_descr == -1)
	{
		std::cout << "Cant open socket" << std::endl;
		return false;
	}

	sockaddr_in server;

	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	if (bind(socket_descr, (sockaddr*) &server, sizeof(server)) == -1)
	{
		std::cout << "Cant bind socket" << std::endl;
		return false;
	}

	if (!dbW::init())
	{
		std::cout << "Cant init DB" << std::endl;
		return false;
	}

	std::cout << "Server init complete" << std::endl;

	return true;
}

void Server::listen()
{
	if (socket_descr == -1)
	{
		std::cout << "Socket not opend!" << std::endl;
		return;
	}

	std::cout << "Server start listen" << std::endl;

	while(true)
	{
		char buffer[BUFLEN] = {};
		sockaddr_in client;
		socklen_t client_len = sizeof(client);

		auto buffer_len = recvfrom(socket_descr, buffer, BUFLEN, 0, (sockaddr*) &client, &client_len);

		buffer[buffer_len] = '\0';

		std::string answer;
		send(client, Logic::parse(buffer, answer));
	}
}

void Server::send(const sockaddr_in& client, const std::string& text)
{
	if (text.length() > BUFLEN - 1)
	{
		std::cout << "Error: text len more buffer!" << std::endl;
		std::cout << "text " << text << std::endl;
		return;
	}

	if (sendto(socket_descr, text.c_str(), text.length(), 0, (sockaddr*) &client, sizeof(client)) < 0)
	{
		std::cout << "Error " << strerror(errno) << " while send text " << text << std::endl;
	}
}

Server::~Server()
{
	if (socket_descr != -1) close(socket_descr);
}
