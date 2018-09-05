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

#define LogError(str, ...) \
do {  \
	if (Logger* logger = GameUtils::GetLogger()) \
	logger->Log(Logger::LogLevel::eError, str, ##__VA_ARGS__); \
} while(0)

#define LogWarning(str, ...) \
do {  \
	if (Logger* logger = GameUtils::GetLogger()) \
	logger->Log(Logger::LogLevel::eWarning, str, ##__VA_ARGS__); \
} while(0)

#define LogInfo(str, ...) \
do {  \
	if (Logger* logger = GameUtils::GetLogger()) \
	logger->Log(Logger::LogLevel::eInfo, str, ##__VA_ARGS__); \
} while(0)

#define LogDebug(str, ...) \
do {  \
	if (Logger* logger = GameUtils::GetLogger()) \
	logger->Log(Logger::LogLevel::eDebug, str, ##__VA_ARGS__); \
} while(0)