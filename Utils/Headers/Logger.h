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
	~Logger();

	template<typename... Ts>
	void Log(LogLevel severity, std::string format, Ts ... args)
	{
		char buffer[255];
		sprintf_s(buffer, format.c_str(), args...);
		std::string logLine(buffer);

		Log_(severity, logLine);
	}

private:
	void Log_(LogLevel loglevel, const std::string& str);
	std::unique_ptr<FWriter> mFileWriter;
};
