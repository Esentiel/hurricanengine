#pragma once

#include "TextureManager.h"

namespace he {
	class ResourcesManager
	{
	public:
		static TextureManager * GetTextureManager();
		static void provideTextureMgr(TextureManager* mgr);

		// static class
		ResourcesManager() = delete;
		~ResourcesManager() = delete;
		ResourcesManager(ResourcesManager&) = delete;
		ResourcesManager& operator=(ResourcesManager) = delete;
	private:
		static TextureManager* mTextureMgr;
	};
}