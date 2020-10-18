#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ObjectCounter.h"
#include "IRenderObject.h"
#include "MultidimensionalVector.h"


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
	unsigned int texture;
	MultidimensionalVector<float, 3, 3, 2> vec;
	void addTexture(const std::string& texturePath);
	
};

