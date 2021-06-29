#pragma once
#include <iostream>
#include <memory>

#include "IObject.h"
#include "../glm/gtc/matrix_transform.hpp"

class IObjectGenerator : virtual public IObject
{
public:
	virtual ~IObjectGenerator() {};
	virtual std::shared_ptr<IObject> generate(glm::vec3 targetPosition)const = 0;
};
