#pragma once

#include <string>
#include <fstream>
#include <queue>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

class Logger;

class LoggerDestroyer
{
	Logger* instanse;
public:
	LoggerDestroyer() = default;
	~LoggerDestroyer();
	void init(Logger* logger);
};

class Logger
{
	static Logger* instanse;
	static LoggerDestroyer destroyer;

	std::fstream os_log_file;

	std::condition_variable event_holder;
	std::mutex lock_queue;
	std::shared_mutex lock_os;
	std::mutex lock_cout;
	std::queue<std::string> queue;
	
	std::future<void> thread;

	bool done = false;
	bool silent_init = false;

protected:

	Logger(const bool& silent_init = false) : silent_init(silent_init) {};

	Logger(const Logger&) = delete;
	Logger& operator = (Logger&) = delete;

	~Logger();

	friend class LoggerDestroyer;

public:

	static Logger* getInstanse(const bool& silent_init = false);
	bool init(const std::string_view& file_name);
	void log(const std::string& str);
	auto read_line(const int& line_num = -1) -> std::string;
	void print(const std::string& str);
};
