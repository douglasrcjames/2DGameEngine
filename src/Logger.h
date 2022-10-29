#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
	public:
		 // static methods can be used by calling them directly!
		static void Log(const std::string& message); // pass reference so op is cheaper!
		static void Err(const std::string& message);

	private:
		
};

#endif