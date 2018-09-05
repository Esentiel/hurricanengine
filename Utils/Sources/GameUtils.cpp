#include "stdafx.h"
#include "GameUtils.h"

std::unique_ptr<Logger> GameUtils::mLogger = nullptr;

GameUtils::GameUtils()
{
}

Logger* GameUtils::GetLogger()
{
	if (mLogger)
	{
		return mLogger.get();
	}
	else
	{
		std::cout << "mLogger is nullptr" << std::endl;
	}
}

void GameUtils::InitLoger(const std::string& path)
{
	mLogger = std::make_unique<Logger>(path);
}


GameUtils::~GameUtils()
{
}
