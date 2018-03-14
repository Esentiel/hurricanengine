
#include "eng_stdafx.h"
#include "TextureManagerImp.h"



he::TextureManagerImp::TextureManagerImp() :
	mStorage(std::make_unique<std::array<Texture, 256>>()),
	mHead(0)
{
}


he::TextureManagerImp::~TextureManagerImp()
{
}

Texture * he::TextureManagerImp::GetTexture(const std::string & path)
{
	auto textureItr = mTextures.find(path);
	if (textureItr != mTextures.end())
	{
		return &(mStorage->at(textureItr->second));
	}
	else
	{
		mStorage->at(mHead).ExtractDDS(path);
		mTextures.insert({ path , mHead });
		mHead++;

		return &(mStorage->at(mHead -1));
	}
}
