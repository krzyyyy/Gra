#pragma once
#include <iostream>
#include <variant>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "..\SharedUtilities\MathHelperFunctions.h"


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
	glm::vec3 ComputeNewDirection(glm::vec3 collisionPoint, glm::vec3 currentDirection) const
	{
		glm::vec3 P = collisionPoint - currentDirection;
		glm::vec3 direction = collisionPoint - Center;
		glm::vec3 Pprojected = Math::ProjectPointOntoStraight(collisionPoint, direction, P);
		glm::vec3 changeVector = Pprojected - P;
		return (P + (2.f * changeVector)) - collisionPoint;
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
		glm::vec3 heightDirection = glm::mat3(objectPosition) * glm::vec3(0, 1, 0);
		return ParametricCilinder{
			.Center = glm::vec3(objectPosition[3].x, objectPosition[3].y, objectPosition[3].z),
			.HeightDirection = heightDirection,
			.R = 0.5 * scale[0],
			.Height = 1. * scale[1],
		};
	}
	glm::vec3 ComputeNewDirection(glm::vec3 collisionPoint, glm::vec3 currentDirection) const
	{
		glm::vec3 collisionPointProjectedOntoMainAxis = Math::ProjectPointOntoStraight(Center, HeightDirection, collisionPoint);
		glm::vec3 P = collisionPoint - currentDirection;
		glm::vec3 direction = collisionPoint - collisionPointProjectedOntoMainAxis;
		glm::vec3 Pprojected = Math::ProjectPointOntoStraight(collisionPoint, direction, P);
		glm::vec3 changeVector = Pprojected - P;
		return (P + (2.f * changeVector)) - collisionPoint;
	}
};
using ParametricModel = std::variant<ParametricSphere, ParametricCilinder>;

