#pragma once
#include <iostream>
#include <variant>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


struct ParametricSphere
{
	glm::vec3 Center = glm::vec3();
	double R = 0.;
};
struct ParametricCilinder
{
	glm::vec3 Center = glm::vec3();
	glm::vec3 HeightDirection = glm::vec3();
	double R = 0.;
	double Height = 0.;
};
using ParametricModel = std::variant<ParametricSphere, ParametricCilinder>;

struct Match
{
	std::size_t QueryIdx;
	std::size_t TrainIdx;
	glm::vec3 ColissionPoint;
};