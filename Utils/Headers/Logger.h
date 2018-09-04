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
	void CalculateLogLevel(LogLevel loglevel, std::ostringstream &Line, tm &current_t, std::chrono::duration<double, std::milli> &ms, const std::string& str);
	void Log(LogLevel loglevel, const std::string& str);
	~Logger();
private:
	FWriter * mMessage;
};

