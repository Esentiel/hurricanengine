#pragma once

#include "stdafx.h"
#include "Logger.h"

class GameUtils
{
public:
	GameUtils();
	static Logger* GetLogger();
	static void InitLoger(const std::string& path);
	~GameUtils();
private: 
	static std::unique_ptr<Logger> mLogger;
};

#define HurLogWarning(str) GameUtils::GetLogger()->Log(Logger::LogLevel::eWarning, str)
#define HurLogError(str) GameUtils::GetLogger()->Log(Logger::LogLevel::eError, str)
#define HurLogDebug(str) GameUtils::GetLogger()->Log(Logger::LogLevel::eDebug, str)
#define HurLogInfo(str) GameUtils::GetLogger()->Log(Logger::LogLevel::eInfo, str)