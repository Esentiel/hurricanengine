#include "GameManager.h"

#include "ResourcesManager.h"
#include "TextureManagerImp.h"



he::GameManager::GameManager()
{
	// initialize res mgr
	mTextureMgr = std::make_unique<TextureManagerImp>();
	ResourcesManager::provideTextureMgr(mTextureMgr.get());
}


he::GameManager::~GameManager()
{
}


Window* he::GameManager::CreateWindow(size_t width, size_t height, const std::string& title, std::array<float, 4> color)
{
	if (mWindow == nullptr)
	{
		mWindow = std::make_unique<Window>(width, height, title, color);
		return mWindow.get();
	}
	else
	{
		return mWindow.get();
	}
}
