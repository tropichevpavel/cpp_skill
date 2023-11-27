
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 4096
#define PORT 65000

void launchServer()
{
	sockaddr_in server, client;

	auto socketDesc = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	bind(socketDesc, (sockaddr*) &server, sizeof(server));

	std::cout << "Socket stat - " << socketDesc << std::endl;

	while (true)
	{
		char buffer[BUFLEN] = {};
		socklen_t cliLen = sizeof(client);
		auto dataSize = recvfrom(socketDesc, buffer, BUFLEN, 0, (sockaddr*) &client, &cliLen);
		// buffer[dataSize] = '\0';

		std::cout << "Message from client: " << buffer << std::endl;

		char message[BUFLEN] = {};
		std::cin >> message;

		if (sendto(socketDesc, message, BUFLEN, 0, (sockaddr*) &client, sizeof(client)) < 0)
			std::cout << "Error while send to client: " << strerror(errno) << std::endl;
		else
			std::cout << "Mesage sent to client: " << message << std::endl;

		std::cout << "Waiting..." << std::endl;
	}

	close(socketDesc);
}

int main()
{
	launchServer();
	return 0;
}

// const char *get_error_text() {

// #if defined(_WIN32)

//     static char message[256] = {0};
//     FormatMessage(
//         FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
//         0, WSAGetLastError(), 0, message, 256, 0);
//     char *nl = strrchr(message, '\n');
//     if (nl) *nl = 0;
//     return message;

// #else

//     return strerror(errno);

// #endif

// }