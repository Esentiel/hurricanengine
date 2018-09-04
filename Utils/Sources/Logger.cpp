#include "stdafx.h"
#include "Logger.h"

Logger::Logger(const std::string& path)
{
	this->mMessage = new FWriter(path);
}

void Logger::CalculateLogLevel(LogLevel loglevel, std::ostringstream& line, tm& current_t, std::chrono::duration<double, std::milli>& milliseconds, const std::string& str)
{
	switch (loglevel)
	{
	case LogLevel::eError:
		line << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "] [Error] " << str;
		break;
	case LogLevel::eWarning:
		line << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "] [Warning] " << str;
		break;
	case LogLevel::eInfo:
		line << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "] [Info] " << str;
		break;
	case LogLevel::eDebug:
		line << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "] [Debug] " << str;
		break;
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
		CalculateLogLevel(loglevel, line, current_t, milliseconds, str);
	}
	mMessage->PushToBuffer(line.str());
	line.str("");
};

Logger::~Logger()
{
	delete this->mMessage;
}