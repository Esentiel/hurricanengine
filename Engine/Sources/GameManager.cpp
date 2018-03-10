#include "GameManager.h"

#include <exception>

#include "ResourcesManager.h"
#include "TextureManagerImp.h"



he::GameManager::GameManager() :
	mMeshStorage(std::make_unique<Meshes>()),
	mMeshesHead(0),
	mShaderFolderPath("../../Resources/shaders/basicShader"),
	mShaderMgr(nullptr),
	mProgramID(0),
	mCamera(nullptr)
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

		// initialize camera
		CreateCamera();

		// initialize shader mgr
		InitializeShaderMgr();

		return mWindow.get();
	}
	else
	{
		return mWindow.get();
	}
}

Camera * he::GameManager::CreateCamera(const Vertex3& pos, float fov, float zNear, float zFar)
{
	if (mWindow == nullptr)
		throw std::exception("Create Window first!");
	auto cam = std::make_unique<Camera>(pos, fov, (float)mWindow->GetWidth() / (float)mWindow->GetHeight(), zNear, zFar);
	mCamera.swap(cam);

	return mCamera.get();
}

Mesh * he::GameManager::CreateMesh(const std::vector<Vertex3>& verteciesPosition, const std::vector<Vertex2>& textureCoords, Texture * texture)
{
	const size_t meshesCnt = mMeshStorage->size();
	mMeshStorage->at(mMeshesHead).InitializeEmptyMesh(verteciesPosition, textureCoords, texture, mProgramID);
	mMeshesHead++;

	return &(mMeshStorage->at(mMeshesHead - 1));
}

void he::GameManager::DrawScene()
{
	for (size_t idx = 0; idx < mMeshesHead; idx++)
	{
		mMeshStorage->at(idx).Draw(*mCamera);
	}
}

void he::GameManager::InitializeShaderMgr()
{
	auto shMgr = std::make_unique<ShaderManager>(mShaderFolderPath);
	mShaderMgr.swap(shMgr);

	// bind shader mgr
	mShaderMgr->Bind();
	mProgramID = mShaderMgr->GetModelLocID();
}
