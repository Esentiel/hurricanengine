#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Vertex_t.h"

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif 

class Transform
{
public:
	RENDERLIBRARY_API Transform(const Vertex3 &pos = Vertex3(), const Vertex3 &rot = Vertex3(), const Vertex3 &scale = Vertex3(1.0f, 1.0f, 1.0f));
	RENDERLIBRARY_API ~Transform();

	RENDERLIBRARY_API const glm::mat4& GetModel();

	RENDERLIBRARY_API Vertex3* GetPos() { return &mPos; }
	RENDERLIBRARY_API Vertex3* GetRot() { return &mRot; }
	RENDERLIBRARY_API Vertex3* GetScale() { return &mScale; }

	RENDERLIBRARY_API void SetPos(const Vertex3& pos) { this->mPos = pos; }
	RENDERLIBRARY_API void SetRot(const Vertex3& rot) { this->mRot = rot; }
	RENDERLIBRARY_API void SetScale(const Vertex3& scale) { this->mScale = scale; }

	// not copyable
	Transform(const Transform&) = delete;
	Transform& operator=(Transform) = delete;
private:
	Vertex3 mPos;
	Vertex3 mRot;
	Vertex3 mScale;
	glm::mat4 mModel;
};