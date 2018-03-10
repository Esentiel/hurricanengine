#include "Mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Mesh::Mesh(const std::vector<Vertex3>& verteciesPosition, const std::vector<Vertex2>& textureCoords, Texture* texture, GLuint programID) :
	mDrawCount(verteciesPosition.size()),
	mTexture(texture),
	mProgram(programID)
{
	// create VertexArrayBuffer
	CreateVertexArrayBuffer(verteciesPosition, textureCoords);
}


Mesh::Mesh() :
	mDrawCount(0),
	mTexture(nullptr),
	mProgram(0)
{
}

Mesh::~Mesh()
{
}

void Mesh::InitializeEmptyMesh(const std::vector<Vertex3>& verteciesPosition, const std::vector<Vertex2>& textureCoords, Texture * texture, unsigned int programID)
{
	if (mDrawCount)
		return;

	// initialize params
	mDrawCount = verteciesPosition.size();
	mTexture = texture;
	mProgram = programID;

	// create VertexArrayBuffer
	CreateVertexArrayBuffer(verteciesPosition, textureCoords);
}

void Mesh::Draw(const Camera &camera)
{
	//bind texture
	mTexture->Bind(true);

	glBindVertexArray(mVerBuffer->GetVertexArrayObject());

	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(mDrawCount));

	glBindVertexArray(0);

	//unbind texture
	mTexture->Bind(false);

	// update position
	auto MVP = camera.GetViewProjection() * mTransform->GetModel();
	glUniformMatrix4fv(mProgram, 1, GL_FALSE, &MVP[0][0]);
}

void Mesh::Move(const Vertex3 & pos)
{
	mTransform->SetPos(pos);
}

void Mesh::Rotate(const Vertex3 & pos)
{
	mTransform->SetRot(pos);
}

void Mesh::Scale(const Vertex3 & pos)
{
	mTransform->SetScale(pos);
}

void Mesh::CreateVertexArrayBuffer(const std::vector<Vertex3>& verteciesPosition, const std::vector<Vertex2>& textureCoords)
{
	// create VertexArrayBuffer
	mVerBuffer = std::make_unique<VertexArray>();
	mVerBuffer->BindVertexCoords(verteciesPosition);
	mVerBuffer->BindTextureCoords(textureCoords);

	mTransform = std::make_unique<Transform>(Vertex3());

	auto model = mTransform->GetModel();

	glUniformMatrix4fv(mProgram, 1, GL_FALSE, &model[0][0]);
}
