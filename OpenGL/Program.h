#pragma once
#include "Shader.h"

class Program
{
public:
	Program();
	//Program(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	void Initialize(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	void CompileAndLink();
	void setUniform(std::tuple<float, float, float, float> vec4, std::string uniformName);
	unsigned int getIdProgram() const
	{
		return idProgram;
	};
	~Program();
private:
	Shader<GL_VERTEX_SHADER> vertexShader;
	Shader<GL_FRAGMENT_SHADER> fragmentShader;
	unsigned int idProgram;
};

