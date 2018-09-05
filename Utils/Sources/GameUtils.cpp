#include "stdafx.h"
#include "GameUtils.h"

std::unique_ptr<Logger> GameUtils::mLogger = nullptr;

GameUtils::GameUtils()
{
}

Logger* GameUtils::GetLogger()
{
	return mLogger.get();
}

void GameUtils::InitLoger(const std::string& path)
{
	mLogger = std::make_unique<Logger>(path);
}


GameUtils::~GameUtils()
{
}
