#pragma once

#include "Vertex_t.h"

#include <glm/gtx/transform.hpp>

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif  

class Camera
{
public:
	RENDERLIBRARY_API Camera(const Vertex3& pos, float fov, float aspect, float zNear, float zFar);
	RENDERLIBRARY_API ~Camera();

	RENDERLIBRARY_API glm::mat4 GetViewProjection() const;

	// not copyable
	Camera(const Camera&) = delete;
	Camera& operator=(Camera) = delete;
private:
	Vertex3 mPos;
	Vertex3 mForward;
	Vertex3 mUp;
	glm::mat4 mProjection;
};

