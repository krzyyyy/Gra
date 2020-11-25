#pragma once
#include <iostream>
#include <random>
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
	Object(glm::vec3 moveDirection_);
	~Object();
	void translate(glm::vec3 translateVector);
	void rotate(float angle, glm::vec3 rotateVector);
	void render(const Program& program);

	using ModelType = Model;

protected:
	void updatePosition();
	glm::mat4 globalPosition;
	glm::vec3 moveDirection;
	float velocity;

};

template<typename Model>
inline Object<Model>::Object():velocity(0.0)
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::uniform_real_distribution<double> dist(-1.0, 1.0);
	
	globalPosition = glm::mat4(1.0f);
	moveDirection = glm::vec3(0, 0, 0);//glm::vec3(dist(mt), dist(mt), dist(mt));//
}

//template<typename Model>
//inline Object<Model>::Object(glm::vec3 moveDirection_):moveDirection(moveDirection_), velocity(0.1)
//{
//}

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
	updatePosition();

	Model::getInstance().Render();

};
template<typename Model>
inline void Object<Model>::updatePosition()
{
	globalPosition = glm::translate(globalPosition, moveDirection * velocity);
};
