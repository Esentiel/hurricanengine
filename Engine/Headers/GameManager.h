#pragma once

#include <memory>
#include <string>
#include <array>

#include <Window.h>
#include <Mesh.h>
#include <ShaderManager.h>

namespace he {
	class TextureManager;
	
	class GameManager
	{
		using Meshes = std::array<Mesh, 256>;
	public:
		GameManager();
		~GameManager();

		Window* CreateWindow(size_t width, size_t height, const std::string& title, std::array<float, 4> color);
		Camera* CreateCamera(const Vertex3f& pos = Vertex3f(0.5f, 0.5f, -3), float fov = 70.f, float zNear = 0.01f, float zFar = 100.0f);

		Mesh* CreateMesh(const std::vector<Vertex3f>& verteciesPosition, const std::vector<Vertex2f>& textureCoords, Texture* texture);
		void DrawScene();

	private:
		std::unique_ptr<TextureManager> mTextureMgr;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<Meshes> mMeshStorage;
		size_t mMeshesHead;
		std::string mShaderFolderPath;
		std::unique_ptr<ShaderManager> mShaderMgr;
		unsigned long mProgramID;
		std::unique_ptr<Camera> mCamera;

		void InitializeShaderMgr();
	};
}