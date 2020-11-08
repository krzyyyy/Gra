#pragma once
#include <iostream>
#include "Program.h"
#include <opencv2/opencv.hpp>

template<typename Model>
class Object
{
public:
	glm::mat4 model2;
	void render(const Program& program);
};

template<typename Model>
void Object< Model>::render(const Program& program)
{
	Model::getInstance().Render();
	program.setUniform(model2, "model");
	program.useProgram();

	Model::getInstance().Render();
	
};