#pragma once

#include "Vertex_t.h"
#include "Matrix4.h"

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif  

class Camera
{
	friend class Mesh;
public:
	RENDERLIBRARY_API Camera(const Vertex3f& pos, float fov, float aspect, float zNear, float zFar);
	RENDERLIBRARY_API ~Camera();

	// not copyable
	Camera(const Camera&) = delete;
	Camera& operator=(Camera) = delete;
private:
	Vertex3f mPos;
	Vertex3f mForward;
	Vertex3f mUp;
	mutable Matrix4 mProjection;

	Matrix4 GetViewProjection() const;
};

