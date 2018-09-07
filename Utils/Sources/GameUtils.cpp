#include "stdafx.h"
#include "GameUtils.h"
#include "Constants.h"

std::unique_ptr<Logger> GameUtils::mLogger = nullptr;

GameUtils::GameUtils()
{
}

Logger* GameUtils::GetLogger()
{
	return mLogger.get();
}

void GameUtils::InitLoger(const std::string& name)
{
	std::string path(LOGPATH);
	path.append(name);
	mLogger = std::make_unique<Logger>(path);
}


GameUtils::~GameUtils()
{
}
