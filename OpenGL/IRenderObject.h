#pragma once

class IRenderObject
{
public:
	virtual void Initialize(float movement) = 0;
	virtual void Render(int shaderProgram) = 0;
	virtual ~IRenderObject() {};
};