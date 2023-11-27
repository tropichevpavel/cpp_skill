
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 4096
#define PORT 65000

void launchClient() {
	sockaddr_in server;

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	auto socketDesc = socket(AF_INET, SOCK_DGRAM, 0);

	if (connect(socketDesc, (sockaddr*) &server, sizeof(server)) < 0) {
		std::cout << "Error connect to server" << std:: endl;
		exit(1);
	}

	while (true)
	{
		std::cout << "Enter message for server" << std::endl;
		std::string in;
		std::getline(std::cin, in);
		const char* message = in.c_str();

		if (sendto(socketDesc, message, in.length(), 0, nullptr, sizeof(server)) < 0)
			std::cout << "Error while send message to server: " << strerror(errno) << std::endl;
		else
			std::cout << "Mesage sent to server: " << message << std::endl;

		std::cout << "Waiting..." << std::endl;

		char buffer[BUFLEN] = {};
		if (recvfrom(socketDesc, buffer, BUFLEN, 0, nullptr, nullptr) < 0)
			std::cout << "Error while accept message from server: " << strerror(errno) << std::endl;
		else
			std::cout << "Message from server: " << buffer << std::endl;
	}

	close(socketDesc);
}

int main() {
	launchClient();
	return 0;
}
