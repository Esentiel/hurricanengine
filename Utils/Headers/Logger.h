#pragma once

#include "FWriter.h"

#ifdef UTILITYLIBRARY_EXPORTS
#define UTILITYLIBRARY_API __declspec(dllexport)
#else
#define UTILITYLIBRARY_API __declspec(dllimport)
#endif

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
	UTILITYLIBRARY_API void Log_(LogLevel loglevel, const std::string& str);
	std::unique_ptr<FWriter> mFileWriter;
};
