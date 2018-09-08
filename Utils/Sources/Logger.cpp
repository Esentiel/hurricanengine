#include "stdafx.h"
#include "Logger.h"

Logger::Logger(const std::string& path)
{
	mFileWriter = std::make_unique<FWriter>(path);
}

std::string Logger::GetLogLevelString(LogLevel loglevel)
{
	std::string level("");
	switch (loglevel)
	{
	case LogLevel::eError:
		level = "ERROR";
		break;
	case LogLevel::eWarning:
		level = "WARNING";
		break;
	case LogLevel::eInfo:
		level = "INFO";
		break;
	case LogLevel::eDebug:
		level = "DEBUG";
		break;
	}

	return level;
}

void Logger::Log_(LogLevel loglevel, const std::string& str)
{
	std::ostringstream logLine;

	std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch()) % 1000;

	time_t currentTime = time(nullptr);
	struct tm current_t;
	
	if (localtime_s(&current_t, &currentTime) == 0)
	{
		std::string enumtostring = GetLogLevelString(loglevel);
		logLine << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "] [" << enumtostring << "] " << str;
	}
	
	mFileWriter->PushToBuffer(logLine.str());
	logLine.str("");
};

Logger::~Logger()
{
}