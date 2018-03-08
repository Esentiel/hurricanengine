#pragma once

#include <memory>
#include <string>

#include <Window.h>

namespace he {
	class TextureManager;
	
	class GameManager
	{
	public:
		GameManager();
		~GameManager();

		Window* CreateWindow(size_t width, size_t height, const std::string& title, std::array<float, 4> color);

	private:
		std::unique_ptr<TextureManager> mTextureMgr;
		std::unique_ptr<Window> mWindow;
	};
}