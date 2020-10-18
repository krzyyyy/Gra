#include "Program.h"


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

void Program::setUniform(const glm::mat4& mat, std::string uniformName)
{
    int uniformLocation = glGetUniformLocation(idProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

Program::~Program()
{
    glDeleteProgram(idProgram);
}
