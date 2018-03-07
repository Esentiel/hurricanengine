#pragma once

#include <vector>


#include "Vertex_t.h"

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif 

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	RENDERLIBRARY_API void BindVertexCoords(const std::vector<Vertex3> &vertexCoords);
	RENDERLIBRARY_API void BindTextureCoords(const std::vector<Vertex2> &TextureCoords);
	unsigned int RENDERLIBRARY_API GetVertexArrayObject() const { return mVertexArrayObject; }

	// not copyable
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray) = delete;
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,

		BUFFER_NUM
	};

	unsigned int mVertexArrayObject;
	unsigned int mVertexArrayBuffers[BUFFER_NUM];
};

