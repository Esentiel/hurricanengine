#include "stdafx.h"

#include "Matrix4.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Matrix4::Matrix4() :
	mMat(nullptr)
{
	
}


Matrix4::Matrix4(glm::mat4 m) :
	mMat(std::make_unique<glm::mat4>(std::move(m)))
{

}

Matrix4::~Matrix4()
{
}

glm::mat4 * Matrix4::GetMat4() const
{
	return mMat.get();
}

void Matrix4::SetMat4(const glm::mat4 * const m)
{
	auto mat = std::make_unique<glm::mat4>(*m);
	mMat.swap(mat);
}
