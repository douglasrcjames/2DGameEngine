#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>

enum LogType {
	INFO,
	WARNING,
	ERROR
};

struct LogEntry {
	LogType type;
	std::string message;
};

class Logger {
	public:
		// static methods can be used by calling them directly!
		static std::vector<LogEntry> messages;
		static void Log(const std::string& message); // pass reference so op is cheaper!
		static void Err(const std::string& message);

	private:
		
};

#endif