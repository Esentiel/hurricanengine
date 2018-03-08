#pragma once

#include <string>

#include "Vertex_t.h"

#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif 

class Texture
{
public:
	RENDERLIBRARY_API Texture();
	RENDERLIBRARY_API Texture(const std::string &filePath);
	RENDERLIBRARY_API ~Texture();

	RENDERLIBRARY_API void Bind(bool flag);
	RENDERLIBRARY_API void ExtractDDS(const std::string &filePath);

	// not copyable
	Texture(Texture&) = delete;
	Texture& operator=(Texture) = delete;
private:
	unsigned int m_texture;
};

