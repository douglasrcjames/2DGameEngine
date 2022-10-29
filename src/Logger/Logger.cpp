#include <iostream>
#include <chrono>
#include <ctime>

#include "Logger.h"

std::vector<LogEntry> Logger::messages;

std::string get_current_time_and_date()
{
	auto const time = std::chrono::current_zone()
		->to_local(std::chrono::system_clock::now());
	return std::format("{:%Y-%m-%d %X}", time);
}

void Logger::Log(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = INFO;
	logEntry.message = "LOG: [" + get_current_time_and_date() + "]: " + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = ERROR;
	logEntry.message = "ERR: [" + get_current_time_and_date() + "]: " + message;
	std::cerr << "\x1B[91m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}