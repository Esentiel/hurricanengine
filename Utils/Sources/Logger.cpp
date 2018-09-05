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
		level = "Error";
		return level;
	case LogLevel::eWarning:
		level = "Warning";
		return level;
	case LogLevel::eInfo:
		level = "Info";
		return level;
	case LogLevel::eDebug:
		level = "Debug";
		return level;
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
		line << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "] [" << enumtostring << "] " << str;
	}
	mFileWriter->PushToBuffer(line.str());
	line.str("");
};

Logger::~Logger()
{
}