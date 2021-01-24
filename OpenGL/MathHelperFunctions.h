#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Math
{
	inline glm::vec3 ProjectPointOntoStraight(glm::vec3 straightPoint, glm::vec3 straightDirection, glm::vec3 projectedPoint)
	{
		straightDirection = glm::normalize(straightDirection);
		double D = -((straightDirection.x * projectedPoint.x) + (straightDirection.y * projectedPoint.y) + (straightDirection.z * projectedPoint.z));
		double t = -(glm::dot(straightDirection, straightPoint) + D);//t = -(Axc+Byc+Czc+D)/(A*A + B*B + C*C)
		glm::vec3 Pprojected = glm::vec3((straightDirection.x * t) + straightPoint.x, (straightDirection.y * t) + straightPoint.y, (straightDirection.z * t) + straightPoint.z);
		return Pprojected;
	}
}