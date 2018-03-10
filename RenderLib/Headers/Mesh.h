#pragma once

#include <vector>
#include <memory>



#include "VertexArray.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif 

class Mesh
{
	friend class Texture;
public:
	RENDERLIBRARY_API Mesh();
	RENDERLIBRARY_API Mesh(const std::vector<Vertex3f>& verteciesPosition, const std::vector<Vertex2f>& textureCoords, Texture* texture, unsigned int programID);
	RENDERLIBRARY_API ~Mesh();

	RENDERLIBRARY_API void InitializeEmptyMesh(const std::vector<Vertex3f>& verteciesPosition, const std::vector<Vertex2f>& textureCoords, Texture* texture, unsigned int programID);

	RENDERLIBRARY_API void Draw(const Camera &camera);
	RENDERLIBRARY_API void Move(const Vertex3f &pos);
	RENDERLIBRARY_API void Rotate(const Vertex3f &pos);
	RENDERLIBRARY_API void Scale(const Vertex3f &pos);
	RENDERLIBRARY_API Transform& GetTransform() { return *mTransform; }

	// not copybale
	Mesh(const Mesh&) = delete;
	Mesh& operator=(Mesh) = delete;
private:
	size_t mDrawCount;
	Texture* mTexture;
	std::unique_ptr<VertexArray> mVerBuffer;
	std::unique_ptr<Transform> mTransform;
	unsigned int mProgram;

	void CreateVertexArrayBuffer(const std::vector<Vertex3f>& verteciesPosition, const std::vector<Vertex2f>& textureCoords);
};

