#pragma once
#include <iostream>
#include "Program.h"
#include <opencv2/opencv.hpp>
#include "ObjectCounter.h"
#include "IObject.h"
#include "glm/gtc/matrix_transform.hpp"

template<typename Model>
class Object:public ObjectCounter<Object< Model>>, public IObject
{
public:
	Object();
	~Object();
	void translate(glm::vec3 translateVector);
	void rotate(float angle, glm::vec3 rotateVector);
	void render(const Program& program);

private:
	glm::mat4 globalPosition;
};

template<typename Model>
inline Object<Model>::Object()
{
	globalPosition = glm::mat4(1.0f);
}

template<typename Model>
inline Object<Model>::~Object()
{
}

template<typename Model>
inline void Object<Model>::translate(glm::vec3 translateVector)
{
	globalPosition = glm::translate(globalPosition, translateVector);
}

template<typename Model>
inline void Object<Model>::rotate(float angle, glm::vec3 rotateVector)
{
	globalPosition = glm::rotate(globalPosition, angle, rotateVector);
}

template<typename Model>
void Object< Model>::render(const Program& program)
{
	program.setUniform(globalPosition, "model");
	program.useProgram();

	Model::getInstance().Render();
	
};