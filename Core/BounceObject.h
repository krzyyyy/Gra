#pragma once
#include <iostream>
#include <cstddef>
#include <vector>
#include <utility>
#include "IObject.h"
#include "ParametricModels.h"

class BounceObjects
{
public:

	std::vector<Match> FindCollisions(std::vector<std::shared_ptr<IObject>>& objects, const std::shared_ptr<IObject>& sword);
	template<typename ParametricModel1, typename ParametricModel2>
	std::pair<bool, glm::vec3> operator()(ParametricModel1 model1, ParametricModel2 model2);
private:
	
	//auto selectBounceMethod(ParametricModel model1, Para)
	template<typename ParametricModel1, typename ParametricModel2>
	auto bounceMethodSelector();
};



template<typename ParametricModel1, typename ParametricModel2>
inline std::pair<bool, glm::vec3> BounceObjects::operator()(ParametricModel1 model1, ParametricModel2 model2)
{
	std::cout << "Wybralem glowna funkcje bez implementacji detekcji kolizji\n";
	return std::make_pair(false, glm::vec3());
}
template<>
inline std::pair<bool, glm::vec3> BounceObjects::operator() < ParametricSphere, ParametricSphere >
(ParametricSphere model1, ParametricSphere model2)
{
	glm::vec3 difference = model1.Center - model2.Center;
	glm::vec3 direction = glm::normalize(difference);

	if (glm::length(difference) > model1.R + model2.R)
	{
		return std::make_pair(false, glm::vec3(0, 0, 0));
	}
	glm::vec3 colisionPoint = model1.Center + (direction * float(model1.R));
	return std::make_pair(true, colisionPoint);
}
template<>
inline std::pair<bool, glm::vec3> BounceObjects::operator() < ParametricSphere, ParametricCilinder>
(ParametricSphere object1, ParametricCilinder object2)
{
	glm::vec3 sphereCenterProjected = Math::ProjectPointOntoStraight(object2.Center, object2.HeightDirection, object1.Center);
	glm::vec3 difference = sphereCenterProjected - object1.Center;
	glm::vec3 differenceCenter = sphereCenterProjected - object2.Center;
	if (glm::length(difference) < object1.R + object2.R)
	{
		if (glm::length(differenceCenter) < object2.Height / 2)
		{
			glm::vec3 direction = glm::normalize(difference);
			glm::vec3 colisionPoint = object1.Center + (direction * float(object1.R));
			return std::make_pair(true, colisionPoint);
		}
		auto directionDotProduct = glm::dot(object2.HeightDirection, differenceCenter);
		glm::vec3 outsiteCenter = glm::vec3();
		if (directionDotProduct > 0)
		{
			outsiteCenter = object2.Center + (object2.HeightDirection * float(object2.Height) / 2.f);
		}
		else
		{
			outsiteCenter = object2.Center - (object2.HeightDirection * float(object2.Height) / 2.f);
		}
		glm::vec3 outsitePointPrejection = Math::ProjectPointOntoStraight(object1.Center, object2.HeightDirection, outsiteCenter);
		glm::vec3 distanceObjectToProjectcionPoint = outsitePointPrejection - object1.Center;
		glm::vec3 projectionDirection = outsitePointPrejection - outsiteCenter;
		if (glm::length(distanceObjectToProjectcionPoint) < object1.R && glm::length(projectionDirection) < object2.R)
		{
			std::cout << "circle Bounce \n";
			return std::make_pair(true, outsitePointPrejection);
		}
		
		projectionDirection = projectionDirection / glm::length(projectionDirection);
		glm::vec3 contourPoint = outsiteCenter + (projectionDirection * float(object2.R));
		glm::vec3 contourPointSphereDifference = object1.Center - contourPoint;
		if (glm::length(contourPointSphereDifference) < object1.R)
		{
			std::cout << "Contour bounce \n";
			return std::make_pair(true, contourPoint);
		}
		
	}

	//glm::vec3 sphereCenterProjected = Math::ProjectPointOntoStraight(object1.Center, object2.HeightDirection, object1.Center);
	return std::make_pair(false, glm::vec3());

}
template<>
inline std::pair<bool, glm::vec3> BounceObjects::operator() < ParametricCilinder, ParametricCilinder >
(ParametricCilinder object1, ParametricCilinder object2)
{
	return std::make_pair(false, glm::vec3());
}

template<typename ParametricModel1, typename ParametricModel2>
inline auto BounceObjects::bounceMethodSelector()
{
	constexpr bool hasBounceMethod = requires()
	{
		BounceObjects::FindBounce(ParametricModel1, ParametricModel2);
	};
	if constexpr (hasBounceMethod)
	{
		return [this](ParametricModel1 model1, ParametricModel2 model2)
		{
			//return this->FindBounce(model1, model2);
		};
	}
	constexpr bool hasBounceMethodWithSwappedArgs = requires()
	{
		BounceObjects::FindBounce(ParametricModel2, ParametricModel1);
	};
	if constexpr (hasBounceMethodWithSwappedArgs)
	{
		return [this](ParametricModel1 model1, ParametricModel2 model2)
		{
			//return this->FindBounce(model2, model1);
		};
	}
	return [this](ParametricModel1 model1, ParametricModel2 model2)
	{
		return std::make_pair(false, glm::vec3());
	};
}
