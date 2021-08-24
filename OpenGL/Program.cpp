#include "Program.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"


Program::Program():  idProgram(0)
{
}

Program::Program(const fs::path& vertexSaderPath, const fs::path& fragmentShaderPath)
{
    Initialize(vertexSaderPath, fragmentShaderPath);
}

Program::Program(Program&& object)noexcept : vertexShader(std::move(object.vertexShader)),
fragmentShader(std::move(object.fragmentShader)), idProgram(std::move(object.idProgram))
{
    object.idProgram = -1;
}

Program& Program::operator=(Program&& object)noexcept
{
    vertexShader = std::move(object.vertexShader);
    fragmentShader = std::move(object.fragmentShader);
    idProgram = std::move(object.idProgram);
    object.idProgram = -1;
    return *this;
    // TODO: insert return statement here
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

void Program::setUniform(float number, std::string uniformName) const
{
    int uniformLocation = glGetUniformLocation(idProgram, uniformName.c_str());
    glUniform1f(uniformLocation, number);
}

void Program::setUniform(bool state, std::string uniformName) const
{
    int uniformLocation = glGetUniformLocation(idProgram, uniformName.c_str());
    glUniform1i(uniformLocation, state);
}

void Program::useProgram()const
{
    glUseProgram(idProgram);
}

void Program::setCameraAndModel(const glm::mat4& model, const Camera& camera)
{
    setUniform(camera.getViewMatrix(), "view");
    setUniform(camera.getProjectionMatrix(), "projection");
    setUniform(model, "model");
}


unsigned int Program::GetID() const
{
    return idProgram;
}

Program::~Program()
{
    if(idProgram>=0)
        glDeleteProgram(idProgram);
}
