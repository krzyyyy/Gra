#pragma once
#include "IShader.h"

template<int T>
class Shader: public IShader
{
public:
	void Initialize( const std::string& shaderSourceCode);
	void Compile();
    int getSharedID();
	~Shader();
private:
	int shaderID;

};

template<int T>
inline void Shader<T>::Initialize( const std::string& shaderSourceCode)
{
	shaderID = glCreateShader(T);
    auto shaderSourceCodeC = shaderSourceCode.c_str();
    glShaderSource(shaderID, 1, &shaderSourceCodeC, NULL);
}

template<int T>
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

template<int T>
inline int Shader<T>::getSharedID()
{
    return shaderID;
}

template<int T>
inline Shader<T>::~Shader()
{
    glDeleteShader(shaderID);
}
