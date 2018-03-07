#pragma once

#include <string>
#include <array>



#ifdef RENDERLIBRARY_EXPORTS  
#define RENDERLIBRARY_API __declspec(dllexport)   
#else  
#define RENDERLIBRARY_API __declspec(dllimport)   
#endif 

class ShaderManager
{
public:
	RENDERLIBRARY_API ShaderManager(const std::string& filePath);
	RENDERLIBRARY_API ~ShaderManager();

	RENDERLIBRARY_API void Bind() const;
	RENDERLIBRARY_API unsigned int GetModelLocID() const { return mModelLoc; }

	// not copyable
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(ShaderManager) = delete;
private:
	enum ShaderType 
	{
		VERTEX_SHADER, 
		FRAGMENT_SHADER,

		SHADER_NUM
	};
	std::string mFilePath;
	unsigned int mProgram;
	std::array<unsigned int,SHADER_NUM> mShaders;
	unsigned int mModelLoc;

	std::string LoadShader(ShaderType type) const;
	void CreateShader(ShaderType type, const std::string& shaderSource);
	void CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string& errorMessage);
};

