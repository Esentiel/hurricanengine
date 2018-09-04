#include "Logger.h"
#include "stdafx.h"
#include <iomanip>
#include <ctime>

Logger::Logger(const std::string& path)
{
	this->mMessage = new FWriter(path);
}

void Logger::Log(LogLevel loglevel, const std::string& str)
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	time_t t = time(nullptr);
	struct tm current_t;
	if (localtime_s(&current_t, &t) == 0)
	{
		switch (loglevel)
		{
		case LogLevel::eError:
			mLine << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count() << "] [Error] " << str;
			break;
		case LogLevel::eWarning:
			mLine << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count() << "] [Warning] " << str;
			break;
		case LogLevel::eInfo:
			mLine << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count() << "] [Info] " << str;
			break;
		case LogLevel::eDebug:
			mLine << std::put_time(&current_t, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count() << "] [Debug] " << str;
			break;
		}
	}
	mMessage->PushToBuffer(mLine.str());
	mLine.str("");
	mMessage->Flush();
};

Logger::~Logger()
{
	delete this->mMessage;
}