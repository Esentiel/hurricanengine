#pragma once

#include <array>
#include <unordered_map>
#include <string>
#include <memory>

#include <Texture.h>

#include "TextureManager.h"

namespace he {
	class TextureManagerImp : public TextureManager
	{
		using TextureStorage = std::unique_ptr<std::array<Texture, 256>>;
	public:
		TextureManagerImp();
		~TextureManagerImp();

		Texture * GetTexture(const std::string& path);
	private:
		TextureStorage mStorage;
		size_t mHead;
		std::unordered_map<std::string, size_t> mTextures;
	};
}
