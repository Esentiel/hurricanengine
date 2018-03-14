#include "stdafx.h"

#include "ResourcesManager.h"

#include "TextureManager.h"

he::TextureManager* he::ResourcesManager::mTextureMgr;

he::TextureManager * he::ResourcesManager::GetTextureManager()
{
	return mTextureMgr;
}

void he::ResourcesManager::provideTextureMgr(TextureManager * mgr)
{
	mTextureMgr = mgr;
}
