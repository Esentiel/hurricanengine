#pragma once

#include <memory>


namespace glm {
	enum precision;

	template <typename, precision>
	struct tmat4x4;

	typedef tmat4x4<float, (precision)0> highp_mat4x4;
	typedef highp_mat4x4 mat4;
}

class Matrix4
{
public:
	Matrix4();
	Matrix4(glm::mat4);
	~Matrix4();

	glm::mat4 * GetMat4() const;
	void SetMat4(const glm::mat4 * const m);
private:
	std::unique_ptr<glm::mat4> mMat;
};