#pragma once

#include "Vertex_t.h"
#include "Matrix4.h"

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif 


class Transform
{
	friend class Mesh;
public:
	RENDERLIBRARY_API Transform(const Vertex3f &pos = Vertex3f(), const Vertex3f &rot = Vertex3f(), const Vertex3f &scale = Vertex3f(1.0f, 1.0f, 1.0f));
	RENDERLIBRARY_API ~Transform();

	RENDERLIBRARY_API Vertex3f* GetPos() { return &mPos; }
	RENDERLIBRARY_API Vertex3f* GetRot() { return &mRot; }
	RENDERLIBRARY_API Vertex3f* GetScale() { return &mScale; }

	RENDERLIBRARY_API void SetPos(const Vertex3f& pos) { this->mPos = pos; }
	RENDERLIBRARY_API void SetRot(const Vertex3f& rot) { this->mRot = rot; }
	RENDERLIBRARY_API void SetScale(const Vertex3f& scale) { this->mScale = scale; }

	// not copyable
	Transform(const Transform&) = delete;
	Transform& operator=(Transform) = delete;
private:
	Vertex3f mPos;
	Vertex3f mRot;
	Vertex3f mScale;
	Matrix4 mModel;

	const Matrix4& GetModel();
};