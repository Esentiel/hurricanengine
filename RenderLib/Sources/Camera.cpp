#include "stdafx.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


Camera::Camera(const Vertex3f& pos, float fov, float aspect, float zNear, float zFar) :
	mPos(pos),
	mForward(0.0f, 0.0f, 1.0f),
	mUp(0.0f, 1.0f, 0.0f)
{
	mProjection.SetMat4(&glm::perspective(fov, aspect, zNear, zFar));
}


Camera::~Camera()
{
}


Matrix4 Camera::GetViewProjection() const
{
	const auto eye = GetGLMVec<glm::vec3>(mPos);
	const auto center = eye + GetGLMVec<glm::vec3>(mForward);
	const auto up = GetGLMVec<glm::vec3>(mUp);

	const auto oldM = *mProjection.GetMat4();
	const auto newM = oldM * glm::lookAt(eye, center, up);

	return std::move(newM);
}