#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace Math
{
	inline glm::vec3 GetVectorPosition(glm::mat4 globalPosiotion)
	{
		return  glm::vec3(globalPosiotion[3].x, globalPosiotion[3].y, globalPosiotion[3].z);
	}
	inline bool IsMovingAway(glm::vec3 object1Center, glm::vec3 object2Center, glm::vec3 object2MovingDirection)
	{
		glm::vec3 difference = object1Center - object2Center;
		difference = glm::normalize(difference);
		auto dotProdact = glm::dot(difference, object2MovingDirection);
		return dotProdact == -1.f;
	}
	inline glm::vec3 ProjectPointOntoStraight(glm::vec3 straightPoint, glm::vec3 straightDirection, glm::vec3 projectedPoint)
	{
		straightDirection = glm::normalize(straightDirection);
		double D = -((straightDirection.x * projectedPoint.x) + (straightDirection.y * projectedPoint.y) + (straightDirection.z * projectedPoint.z));
		double t = -(glm::dot(straightDirection, straightPoint) + D);//t = -(Axc+Byc+Czc+D)/(A*A + B*B + C*C)
		glm::vec3 Pprojected = glm::vec3((straightDirection.x * t) + straightPoint.x, (straightDirection.y * t) + straightPoint.y, (straightDirection.z * t) + straightPoint.z);
		return Pprojected;
	}
}