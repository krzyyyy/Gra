#pragma once
#include <iostream>
#include <memory>
#include "Shader.h"
#include "Camera.h"
#include "..\glm\glm.hpp"

class Program
{
public:
	Program();
	Program(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	Program(const Program& object) = delete;
	Program(Program&& object) noexcept;
	Program& operator=(const Program& object) = delete;
	Program& operator=(Program&& object)noexcept;

	//Program(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	void Initialize(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath);
	void CompileAndLink();
	void setUniform(const glm::mat4& mat, std::string uniformName)const;
	void setUniform(const glm::vec3& vec, std::string uniformName)const;
	void setUniform(float number, std::string uniformName)const;
	void setUniform(bool state, std::string uniformName)const;
	void useProgram()const;
	void setCameraAndModel( const glm::mat4& model, const Camera& camera);
	unsigned int GetID() const;
	~Program();
private:
	Shader<GL_VERTEX_SHADER> vertexShader;
	Shader<GL_FRAGMENT_SHADER> fragmentShader;
	int idProgram;
};

