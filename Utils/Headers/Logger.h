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
	std::string GetLogLevelString(LogLevel loglevel);
	void Log(LogLevel loglevel, const std::string& str);
	~Logger();
private:
	std::unique_ptr<FWriter> mPointerToFile;
};


