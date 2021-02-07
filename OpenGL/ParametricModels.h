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
	static ParametricSphere ComputeParametricModel(const glm::mat4& objectPosition, const glm::vec3& scale)
	{
		return ParametricSphere{
			.Center = glm::vec3(objectPosition[3].x, objectPosition[3].y, objectPosition[3].z),
			.R = 0.5,
		};
	}
};
struct ParametricCilinder
{
	glm::vec3 Center = glm::vec3();
	glm::vec3 HeightDirection = glm::vec3();
	double R = 0.;
	double Height = 0.;
	static ParametricCilinder ComputeParametricModel(const glm::mat4& objectPosition, const glm::vec3& scale)
	{
		auto vector = glm::vec3(objectPosition[0][0], objectPosition[0][1], objectPosition[0][2]);
		glm::vec3 heigntDirection = glm::mat3(objectPosition) * glm::vec3(0, 0, 1);
		return ParametricCilinder{
			.Center = glm::vec3(objectPosition[3].x, objectPosition[3].y, objectPosition[3].z),
			.HeightDirection = heigntDirection,
			.R = 0.5 * scale[0],
			.Height = 1. * scale[2],
		};
	}
};
using ParametricModel = std::variant<ParametricSphere, ParametricCilinder>;

struct Match
{
	std::size_t QueryIdx;
	std::size_t TrainIdx;
	glm::vec3 ColissionPoint;
};