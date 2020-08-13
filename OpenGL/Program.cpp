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

void Program::setUniform(std::tuple<float, float, float, float> vec4, std::string uniformName)
{
    auto [skalar1, skalar2, skalar3, skalar4] = vec4;
    int vertexColorLocation = glGetUniformLocation(idProgram, "ourColor");
    glUniform4f(vertexColorLocation, skalar1, skalar2, skalar3, skalar4);
}

Program::~Program()
{
    glDeleteProgram(idProgram);
}
