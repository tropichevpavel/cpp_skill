
#include "core/Logger.h"
#include "core/UDPServer.h"


int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (!strcmp(argv[i], "-l"))
			{
				int line_num = -1;
				try { if (i + 2 <= argc) line_num = std::stoi(argv[i + 1]); } catch (...) { std::cout << "Error '-l' value! Only numeric! Use default -1 value" << std::endl; }

				Logger* logger = Logger::getInstanse(true);
				if (!logger->init(logger_file))
				{
					std::cout << "Cant init logger!" << std::endl;
					return 1;
				}
				std::cout << logger->read_line(line_num) << std::endl;
			}
		}

		return 0;
	}

	Server server;
	if (server.init()) server.listen();
	return 0;
}
