#pragma once

#include "stdafx.h"
#include "Logger.h"

#ifdef UTILITYLIBRARY_EXPORTS
#define UTILITYLIBRARY_API __declspec(dllexport)
#else
#define UTILITYLIBRARY_API __declspec(dllimport)
#endif

class GameUtils
{
public:
	GameUtils();
	static UTILITYLIBRARY_API Logger* GetLogger();
	static UTILITYLIBRARY_API void InitLoger(const std::string& name);
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