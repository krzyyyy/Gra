#pragma once
#include <iostream>
#include <chrono>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

class IObject
{
public:
	virtual ~IObject() {};
	virtual void translate(glm::vec3 translateVector) = 0;
	virtual void rotate(float angle, glm::vec3 rotateVector) = 0;
	virtual glm::mat4 getGlobalPosition()const = 0;
	virtual void loadModel()const = 0;
	virtual void updatePosition(std::chrono::duration<double> deltaT) =0;
};