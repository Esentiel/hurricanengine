#include "stdafx.h"
#include "Logger.h"

Logger::Logger(const std::string& path)
{
	mPointerToFile = std::make_unique<FWriter>(path);
}

std::string Logger::GetLogLevelString(LogLevel loglevel)
{
	switch (loglevel)
	{
	case LogLevel::eError:
		return "] [Error] ";
	case LogLevel::eWarning:
		return "] [Warning] ";
	case LogLevel::eInfo:
		return "] [Info] ";
	case LogLevel::eDebug:
		return "] [Debug] ";
	}
}

void Logger::Log(LogLevel loglevel, const std::string& str)
{
	std::ostringstream line;

	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	time_t timer = time(nullptr);
	struct tm current_t;
	if (localtime_s(&current_t, &timer) == 0)
	{
		std::string enumtostring = GetLogLevelString(loglevel);
		line << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << enumtostring << str;
	}
	mPointerToFile->PushToBuffer(line.str());
	line.str("");
};

Logger::~Logger()
{
}