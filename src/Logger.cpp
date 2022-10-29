#include <iostream>
#include <chrono>
#include <ctime>

#include "Logger.h"

std::string get_current_time_and_date()
{
	auto const time = std::chrono::current_zone()
		->to_local(std::chrono::system_clock::now());
	return std::format("{:%Y-%m-%d %X}", time);
}

void Logger::Log(const std::string& message) {
	std::string output = "LOG: [" + get_current_time_and_date() + "]: " + message;
	std::cout << "\x1B[32m" << output << "\033[0m" << std::endl;
}

void Logger::Err(const std::string& message) {
	std::string output = "ERR: [" + get_current_time_and_date() + "]: " + message;
	std::cerr << "\x1B[91m" << output << "\033[0m" << std::endl;
}