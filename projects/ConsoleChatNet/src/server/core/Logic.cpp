#include "Logic.h"

#include <iostream>

#include "DBWrapper.h"
#include "UserSQL.h"

auto Logic::parse(const std::string& buffer, std::string& answer) -> std::string&
{
	int user_id = 0;
	int command = -1;

	auto next_part = [](const std::string& data, const bool& is_new = false, const bool& last_part = false, const char delimetr = ' ') -> std::string
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
		std::string part = next_part(buffer, true);
		user_id = std::stoi(part);
		part = next_part(buffer);
		command = std::stoi(part);
	}
	catch (...)
	{
		// std::cout << buffer << " :::" << buffer.substr(0, pos) << "//" << buffer.substr(++pos, abs(pos - (pos = buffer.find_first_of(' ', pos)))) << std::endl;
	}

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
				std::cout << "Server auth client" << std::endl;
				answer = std::to_string(user->get_id()) + " " + user->get_name();
			}
			else
			{
				std::cout << "Server error login" << std::endl;
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
				std::cout << "Server reg client" << std::endl;
				answer = "1 1";
			}
			else
			{
				std::cout << "Server error reg" << std::endl;
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
			else std::cout << "Unauthorized access to msgs" << std::endl;
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
				std::cout << "Server add msg error" << std::endl;
				break;
			}

			if (user_id > 0 && dbW::add_msg(user_id, chat_id, user_id_to, next_part(buffer, false, true)))
			{
				answer = std::to_string(SEND) + " 1";
				std::cout << "Server msg new" << std::endl;
			}
			break;
		}

		case GET_CHAT_ID_LAST:
		{
			if (user_id > 0) answer = " " + std::to_string(dbW::get_chat_id_last(user_id));
			break;
		}

		default: std::cout << "Unknow command " << command << " from user " << user_id << std::endl;
	}

	return answer;
};
