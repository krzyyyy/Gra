#pragma once
#include <iostream>
#include <chrono>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

class IObject
{
public:
	virtual ~IObject() {};
	virtual void Translate(glm::vec3 translateVector) = 0;
	virtual void Rotate(float angle, glm::vec3 rotateVector) = 0;
	virtual glm::mat4 GetGlobalPosition()const = 0;
	virtual void LoadModel()const = 0;
	virtual void UpdatePosition(std::chrono::duration<double> deltaT) =0;
	virtual std::string GetObjectType()const =0;
};