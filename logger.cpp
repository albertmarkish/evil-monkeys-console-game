#include "logger.h"

Logger::Logger(short line)
{
	lineNumber = line;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	nextCursorPosition.X = 0;
	nextCursorPosition.Y = 0;
}

void Logger::log(const char* message)
{
	COORD cursorPositionBackup = getCursorPosition();
	nextCursorPosition.Y = lineNumber;
	SetConsoleCursorPosition(hStdout, nextCursorPosition);

	cout << message;

	SetConsoleCursorPosition(hStdout, cursorPositionBackup);

	lineNumber++;
}

void Logger::log(std::string message)
{
	COORD cursorPositionBackup = getCursorPosition();
	nextCursorPosition.Y = lineNumber;
	SetConsoleCursorPosition(hStdout, nextCursorPosition);

	cout << message;

	SetConsoleCursorPosition(hStdout, cursorPositionBackup);

	lineNumber++;
}

COORD Logger::getCursorPosition(void)
{
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		printf("GetConsoleScreenBufferInfo failed %d\n", GetLastError());
	}

	return csbiInfo.dwCursorPosition;
}
