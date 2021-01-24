#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "IObject.h"
#include "ParametricModels.h"
class BounceObjects
{
public:
	std::vector<Match> FindCollisions(std::vector<std::shared_ptr<IObject>>& objects, const std::shared_ptr<IObject>& sword);
	std::pair<bool, glm::vec3> FindBounce( ParametricSphere object1, ParametricSphere object2);
	std::pair<bool, glm::vec3> FindBounce(ParametricSphere object1, ParametricCilinder object2);
};


