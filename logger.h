#pragma once

#include <Windows.h>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

class Logger
{
public:
	Logger(short lineNumber = 27);
	void log(const char* message);
	void log(std::string message);

	template<typename ... Args>
	static std::string stringFormat(const std::string& format, Args ... args);

private:
	short lineNumber; //where to begin output
	HANDLE hStdout;
	COORD nextCursorPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	COORD getCursorPosition(void);
};

template<typename ... Args>
std::string Logger::stringFormat(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
