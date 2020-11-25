#pragma once
#include <iostream>
#include <memory>

#include "IObject.h"
#include "glm/gtc/matrix_transform.hpp"

class IObjectGenerator
{
public:
	virtual std::unique_ptr<IObject> generate(glm::vec3 targetPosition) = 0;
};
