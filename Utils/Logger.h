#pragma once
#include "FWriter.h"

class Logger
{
public:
	enum class LogLevel
	{
		eError = 0,
		eWarning,
		eInfo,
		eDebug
	};
	Logger(const std::string& path);
	void Log(LogLevel loglevel, const std::string& str);
	~Logger();
private:
	FWriter * mMessage;
	std::ostringstream mLine;
};

