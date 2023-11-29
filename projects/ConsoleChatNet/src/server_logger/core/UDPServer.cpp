#include <unistd.h>
#include <sstream>

#include "UDPServer.h"
#include "DBWrapper.h"

bool Server::init()
{
	if (socket_descr != -1) return false;

	logger = Logger::getInstanse();
	if (!logger->init(logger_file))
	{
		std::cout << "Cant init Logger" << std::endl;
		return false;
	}

	socket_descr = socket(AF_INET, SOCK_DGRAM, 0);

	if (socket_descr == -1)
	{
		logger->log("Cant open socket");
		return false;
	}

	sockaddr_in server;

	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	if (bind(socket_descr, (sockaddr*) &server, sizeof(server)) == -1)
	{
		logger->log("Cant bind socket");
		return false;
	}

	if (!dbW::init())
	{
		logger->log("Cant init DB");
		return false;
	}

	logger->log("Server init complete");

	return true;
}

void Server::listen()
{
	if (socket_descr == -1)
	{
		logger->log("Socket not opend!");
		return;
	}

	logger->log("Server start listen");

	while(true)
	{
		char buffer[BUFLEN] = {};
		sockaddr_in client;
		socklen_t client_len = sizeof(client);

		auto buffer_len = recvfrom(socket_descr, buffer, BUFLEN, 0, (sockaddr*) &client, &client_len);

		buffer[buffer_len] = '\0';

		std::string answer;
		send(client, parse(buffer, answer));
	}
}

void Server::send(const sockaddr_in& client, const std::string& text)
{
	if (text.length() > BUFLEN - 1)
	{
		logger->log("Error: text len more buffer!");
		return;
	}

	if (sendto(socket_descr, text.c_str(), text.length(), 0, (sockaddr*) &client, sizeof(client)) < 0)
	{
		logger->log((std::stringstream() << "Error " << strerror(errno) << " while send text").str());
	}
}

auto Server::parse(const std::string& buffer, std::string& answer) -> std::string&
{
	int user_id = 0;
	int command = -1;

	auto next_part = [] (const std::string& data, const bool& is_new = false, const bool& last_part = false, const char delimetr = ' ') -> std::string
	{
		static size_t pos_cur = 0;
		static int pos_next = 0;

		if (last_part) return data.substr(pos_next + 1);

		if (is_new || !pos_next)
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

	try
	{
		user_id = std::stoi(next_part(buffer, true));
		command = std::stoi(next_part(buffer));
	}
	catch (...) { }

	answer = "-1";

	switch(command)
	{
		case LOGIN:
		{
			std::string login = next_part(buffer);
			std::string pass = next_part(buffer);
			dbW::User* user = nullptr;
			if (dbW::auth(login, pass, user))
			{
				logger->log("Server auth client! user: " + login);
				answer = std::to_string(user->get_id()) + " " + user->get_name();
			}
			else
			{
				logger->log("Server error login! user: " + login + " pass: " + pass);
			}
			if (user) delete user;
			break;
		}

		case REGISTER:
		{
			std::string login = next_part(buffer),
						pass = next_part(buffer),
						name = next_part(buffer);

			if (dbW::add_user(login, pass, name))
			{
				logger->log("Server reg client! user: " + login + " pass: " + pass + " name: " + name);
				answer = "1 1";
			}
			else
			{
				logger->log("Server error reg! user: " + login + " pass: " + pass + " name: " + name);
			}
			break;
		}

		case GET_USERS:
		{
			answer = dbW::get_users();
			if (!answer.size()) answer = "-1";
			break;
		}

		case GET_MESSAGES:
		{
			if (user_id > 0)
			{
				answer = dbW::get_msgs(user_id);
				if (!answer.size()) answer = "-1";
			}
			else logger->log("Unauthorized access to msgs");
			break;
		}

		case SEND:
		{
			int chat_id = 0,
				user_id_to = 0;

			try
			{
				chat_id = std::stoi(next_part(buffer));
				user_id_to = std::stoi(next_part(buffer));
			}
			catch (...)
			{
				logger->log("Server add msg error! Error while parse request!");
				break;
			}

			std::string text = next_part(buffer, false, true);

			if (user_id > 0 && dbW::add_msg(user_id, chat_id, user_id_to, text))
			{
				answer = std::to_string(SEND) + " 1";
				logger->log((std::stringstream() << "Server msg new: from " << user_id << " to " << user_id_to << " text: " << text).str());
			}
			else logger->log("Server add msg error! Unauthorized user or DB error!");
			break;
		}

		case GET_CHAT_ID_LAST:
		{
			if (user_id > 0) answer = " " + std::to_string(dbW::get_chat_id_last(user_id));
			break;
		}

		default: logger->log("Unknow command " + std::to_string(command) + " from user " + std::to_string(user_id));
	}

	return answer;
}

Server::~Server()
{
	if (socket_descr != -1) close(socket_descr);
}
