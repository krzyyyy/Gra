#include "Program.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


Program::Program():  idProgram(0)
{
}

void Program::Initialize(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath)
{
	vertexShader.Initialize(vertexSaderPath);
	fragmentShader.Initialize(fragmentShaderPath);
}

void Program::CompileAndLink()
{
    vertexShader.Compile();
    fragmentShader.Compile();


    // link shaders
    idProgram = glCreateProgram();
    glAttachShader(idProgram, vertexShader.getSharedID());
    glAttachShader(idProgram, fragmentShader.getSharedID());
    glLinkProgram(idProgram);
}

void Program::setUniform(const glm::mat4& mat, std::string uniformName)const
{
    int uniformLocation = glGetUniformLocation(idProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

void Program::setUniform(const glm::vec3& vec, std::string uniformName) const
{
    int uniformLocation = glGetUniformLocation(idProgram, uniformName.c_str());
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vec));
}

void Program::useProgram()const
{
    glUseProgram(idProgram);
}

Program::~Program()
{
    glDeleteProgram(idProgram);
}
