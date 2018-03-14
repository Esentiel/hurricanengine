#include "stdafx.h"


#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


Transform::Transform(const Vertex3f &pos, const Vertex3f &rot, const Vertex3f &scale) :
	mPos(pos),
	mRot(rot),
	mScale(scale)
{

}


Transform::~Transform()
{
}

const Matrix4& Transform::GetModel()
{
	const glm::mat4 posMat = glm::translate(GetGLMVec<glm::vec3>(mPos));
	const glm::mat4 scaleMat = glm::scale(GetGLMVec<glm::vec3>(mScale));
	const glm::mat4 rotX = glm::rotate(mRot.x(), glm::vec3(1.0, 0.0, 0.0));
	const glm::mat4 rotY = glm::rotate(mRot.y(), glm::vec3(0.0, 1.0, 0.0));
	const glm::mat4 rotZ = glm::rotate(mRot.z(), glm::vec3(0.0, 0.0, 1.0));
	const glm::mat4 rotMat = rotX * rotY * rotZ;

	const auto newModel = posMat * rotMat * scaleMat;
	mModel.SetMat4(&newModel);

	return mModel;
}
