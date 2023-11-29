
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "Logger.h"

Logger* Logger::instanse = nullptr;
LoggerDestroyer Logger::destroyer;

bool Logger::init(const std::string_view& file_name)
{
	if (os_log_file) os_log_file.close();

	os_log_file.open(file_name, std::ios::in | std::ios::out | std::ios::ate);
	if (!os_log_file) os_log_file.open(file_name, std::ios::in | std::ios::out | std::ios::trunc);

	if (!os_log_file) return false;

	if (!silent_init) log("Init Logger io file " + std::string(file_name));

	thread = std::async(std::launch::async, [this] ()
	{
		if (!silent_init) log("Init logger file io thread");
		while (true)
		{
			std::unique_lock<std::mutex> mutex_holder(lock_queue);

			if (done && queue.empty()) break;

			if (queue.empty())
			{
				event_holder.wait(mutex_holder, [this] () { return !queue.empty() || done; });
			}

			while (queue.size())
			{
				if (os_log_file)
				{
					std::lock_guard<std::shared_mutex> tmp_lock_os(lock_os);
					os_log_file << queue.front() << std::endl;
				}
				queue.pop();
			}
		}
	});

	return true;
}

void Logger::log(const std::string& str)
{
	auto time_cur = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::string tmp = (std::stringstream() << " [" << std::put_time(std::localtime(&time_cur), "%Y-%m-%d %H.%M.%S") << "]: " << str).str();

	print(tmp);
	if (os_log_file)
	{
		{
			std::lock_guard<std::mutex> tmp_lock(lock_queue);
			queue.push(tmp);
		}
		event_holder.notify_one();
	}
}

auto Logger::read_line(const int& line_num) -> std::string
{
	if (line_num < -1) return "";

	std::string last_line;

	lock_os.lock_shared();

	bool find = false;
	size_t counter = 0;
	if (line_num == -1)
	{
		counter = 2;
		os_log_file.seekg(-1, std::ios_base::end);
	}
	else
	{
		os_log_file.seekg(0, std::ios_base::beg);
		counter = line_num - 1;
		find = !counter;
	}

	while (!find)
	{
		if (os_log_file.eof()) break;

		char ch;
		os_log_file.get(ch);

		if (line_num == -1 && (int) os_log_file.tellg() <= 1)
		{
			os_log_file.seekg(0);
			find = true;
		}
		else if (ch == '\n' && !--counter)
		{
			find = true;
		}
		else if (line_num == -1)
		{
			os_log_file.seekg(-2, std::ios_base::cur);
		}
	}

	std::getline(os_log_file, last_line);
	os_log_file.seekg(-1, std::ios_base::end);
	lock_os.unlock_shared();

	return last_line;
}

void Logger::print(const std::string& str)
{
	std::lock_guard<std::mutex> tmp_lock_cout(lock_cout);
	std::cout << str << std::endl;
}

auto Logger::getInstanse(const bool& silent_init) -> Logger*
{
	if (!instanse)
	{
		instanse = new Logger(silent_init);
		if (!silent_init) instanse->log("Init Logger");
		destroyer.init(instanse);
	}

	return instanse;
}

Logger::~Logger()
{
	done = true;
	event_holder.notify_one();
	if (thread.valid()) thread.wait();
	if (os_log_file) os_log_file.close();
}

void LoggerDestroyer::init(Logger* logger)
{
	instanse = logger;
}

LoggerDestroyer::~LoggerDestroyer()
{
	if (instanse) delete instanse; 
}