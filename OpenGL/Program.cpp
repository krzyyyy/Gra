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

void Program::useProgram()const
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -7.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    setUniform(view, "view");
    setUniform(projection, "projection");
    glUseProgram(idProgram);
}

Program::~Program()
{
    glDeleteProgram(idProgram);
}
