#pragma once
#include "Shader.h"
#include "glm/glm.hpp"

class Program
{
public:
	Program();
	//Program(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	void Initialize(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	void CompileAndLink();
	void setUniform(const glm::mat4& mat, std::string uniformName)const;
	void setUniform(const glm::vec3& vec, std::string uniformName)const;
	void useProgram()const;
	~Program();
private:
	Shader<GL_VERTEX_SHADER> vertexShader;
	Shader<GL_FRAGMENT_SHADER> fragmentShader;
	unsigned int idProgram;
};
