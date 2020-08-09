#pragma once
#include "ShaderEnum.h"
#include <iostream>

class IShader
{
public:
	virtual void Initialize(const std::string& shaderSourceCode ) =0;
	virtual void Compile() = 0;
	virtual ~IShader() {};
};