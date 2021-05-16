#pragma once
#include <iostream>
#include <chrono>
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/glm.hpp"

#include "ParametricModels.h"

class IObject
{
public:
	virtual ~IObject() {};
	//transformation functions
	virtual void Translate(glm::vec3 translateVector) = 0;
	virtual void Rotate(float angle, glm::vec3 rotateVector) = 0;
	virtual void Scale(glm::vec3 scaleFactor) =0;
	virtual void UpdatePosition(std::chrono::duration<double> deltaT) = 0;
	// geters
	virtual glm::mat4 GetGlobalPosition()const = 0;
	virtual std::string GetObjectType()const =0;
	virtual std::string GetObjectModel() const = 0;

	virtual ParametricModel GetParametricModel()const = 0;
	virtual void BounceReaction(glm::vec3 collisionPoint) = 0;

	virtual bool IsMovingAway(const std::shared_ptr<IObject>& object) = 0;
};

struct Match
{
	std::shared_ptr<IObject> QueryIdx;
	std::shared_ptr<IObject> TrainIdx;
	glm::vec3 ColissionPoint;
};