#pragma once
#include "ParametricModels.h"

class IBounceable
{
public:
	virtual ParametricModel GetParametricModel()const = 0;
	virtual void Bounce(glm::vec3 collisionPoint) = 0;
};
