#pragma once
#include "IShader.h"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;

template<unsigned int T>
class Shader: public IShader
{
public:
    Shader();
    Shader(const Shader& object) = delete;
    Shader(Shader&& object);
    Shader& operator=(const Shader& object) = delete;
    Shader& operator=(Shader&& object);
	void Initialize( const std::string& shaderSourceCode);
    void Initialize(const fs::path& shaderPath);
	void Compile();
    unsigned int getSharedID();
	~Shader();
private:
	int shaderID;

};

template<unsigned int T>
inline Shader<T>::Shader():shaderID(-1)
{
}

template<unsigned int T>
inline Shader<T>::Shader(Shader&& object) : shaderID(std::move(object.shaderID))
{
    object.shaderID = -1;
}

template<unsigned int T>
inline Shader<T>& Shader<T>::operator=(Shader&& object)
{
    shaderID = std::move(object.shaderID);
    object.shaderID = -1;
    return *this;
}

template<unsigned unsigned int T>
inline void Shader<T>::Initialize( const std::string& shaderSourceCode)
{
	shaderID = glCreateShader(T);
    auto shaderSourceCodeC = shaderSourceCode.c_str();
    glShaderSource(shaderID, 1, &shaderSourceCodeC, NULL);
}

template<unsigned unsigned int T>
inline void Shader<T>::Initialize(const fs::path& shaderPath)
{
    auto shaderFile = std::ifstream(shaderPath, std::ios::in);
    if (!shaderFile.is_open())
    {
        std::cout << "I can't open file" << shaderPath << std::endl;
        throw std::exception("I can't open file");
    }
    auto shaderContent = std::stringstream();
    shaderContent << shaderFile.rdbuf();
    shaderFile.close();
    shaderID = glCreateShader(T);
    std::string shaderCode = shaderContent.str();
    auto shaderCodeC = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderCodeC, NULL);

}

template<unsigned int T>
inline void Shader<T>::Compile()
{
    
    glCompileShader(shaderID);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::string errorMessage = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << errorMessage << infoLog << std::endl;
        std::exception exception = std::exception((errorMessage+ infoLog).c_str());
        throw exception;
    }
}

template<unsigned int T>
inline unsigned int Shader<T>::getSharedID()
{
    return shaderID;
}

template<unsigned int T>
inline Shader<T>::~Shader()
{
    if(shaderID>=0)
        glDeleteShader(shaderID);
}
