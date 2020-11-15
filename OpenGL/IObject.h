#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "Program.h"

class IObject
{
public:
	virtual ~IObject() {};
	virtual void translate(glm::vec3 translateVector) = 0;
	virtual void rotate(float angle, glm::vec3 rotateVector) = 0;
	virtual void render(const Program& program) = 0;
};