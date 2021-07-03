#pragma once
#include "IObject.h"

class IBulletPrototype
{
public :
	virtual std::shared_ptr<IObject> Clone(glm::vec3 beginTrajectory, glm::vec3 pointOnTrajectory) const = 0;
};