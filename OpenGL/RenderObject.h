#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ObjectCounter.h"
#include "IRenderObject.h"


class RenderObject : public ObjectCounter<RenderObject>, public IRenderObject
{
public:
	RenderObject();
	void Initialize(float movement);
	void Render(const Program& program);
	~RenderObject();



private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	
};

