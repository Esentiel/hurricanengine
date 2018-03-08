#pragma once

#include <string>

class Texture;

namespace he {
	class TextureManager
	{
	public:
		TextureManager() {};
		virtual Texture * GetTexture(const std::string& path) = 0;
		virtual ~TextureManager() {};
	};
}