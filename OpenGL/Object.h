#pragma once
#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>
#include "ObjectCounter.h"
#include "IObject.h"
//#include "glm/gtc/matrix_transform.hpp"
#include "RenderObject.h"
#include "IBounceable.h"
#include "MathHelperFunctions.h"


template<typename Model>
class Object:public ObjectCounter<Object<typename Model>>, public IObject, public IBounceable
{
public:
	Object();
	Object(std::string objectType_, std::string modelType_);
	Object(glm::vec3 moveDirection_, std::string objectType_, std::string modelType_);
	Object(const Object& object) = default;
	Object(Object&& object) = default;
	Object& operator=(const Object& object) = default;
	Object& operator=(Object&& object) = default;
	~Object();
	//transformation functions
	void Translate(glm::vec3 translateVector) override;
	void Rotate(float angle, glm::vec3 rotateVector) override;
	void Scale(glm::vec3 scaleFactor) override;
	void UpdatePosition(std::chrono::duration<double> deltaT) override;
	//geters
	glm::mat4 GetGlobalPosition()  const override;
	std::string GetObjectType()  const override;
	std::string GetObjectModel() const override;
	//IBounceable methods
	ParametricModel GetParametricModel()const;
	void Bounce(glm::vec3 collisionPoint);

protected:
	glm::vec3 getPosition()const;
	glm::vec3 scale;
	glm::mat4 globalPosition;
	glm::vec3 moveDirection;
	std::string objectType;
	std::string modelType;

};

template<typename Model>
inline Object<typename Model>::Object()
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::uniform_real_distribution<double> dist(-1.0, 1.0);
	scale = glm::vec3(1., 1., 1.);
	globalPosition = glm::mat4(1.0f);
	moveDirection = glm::vec3(0, 0, 0);//glm::vec3(dist(mt), dist(mt), dist(mt));//
	objectType = "Non";
	modelType = "Non"; 
}

template<typename Model>
inline Object<typename Model>::Object(std::string objectType_, std::string modelType_):globalPosition(glm::mat4(1.0f)),scale(1., 1., 1.),
moveDirection(glm::vec3(0, 0, 0)), objectType(objectType_), modelType(modelType_)
{
}

template<typename Model>
inline Object<typename Model>::Object(glm::vec3 moveDirection_, std::string objectType_, std::string modelType_):scale(1., 1.,1.),
moveDirection(moveDirection_), objectType(objectType_), modelType(modelType_)
{
	globalPosition = glm::mat4(1.0f);
}

template<typename Model>
inline Object<typename Model>::~Object()
{
}

template<typename Model>
inline void Object<typename Model>::Translate(glm::vec3 translateVector)
{
	globalPosition = glm::translate(globalPosition, translateVector);
}

template<typename Model>
inline void Object<typename Model>::Rotate(float angle, glm::vec3 rotateVector)
{
	globalPosition = glm::rotate(globalPosition, angle, rotateVector);
}

template<typename Model>
inline void Object<Model>::Scale(glm::vec3 scaleFactor)
{
	scale = scale * scaleFactor;
}

template<typename Model>
inline ParametricModel Object<Model>::GetParametricModel()const
{
	return Model::ComputeParametricModel(globalPosition, scale);
}
template<typename Model>
inline void Object<Model>::Bounce(glm::vec3 collisionPoint)
{
	//moveDirection = -moveDirection;
	glm::vec3 P = collisionPoint - moveDirection;
	glm::vec3 centerPosition = getPosition();
	glm::vec3 direction = collisionPoint - centerPosition;
	glm::vec3 Pprojected = Math::ProjectPointOntoStraight(collisionPoint, direction, P);
	glm::vec3 changeVector = Pprojected - P; 
	moveDirection = (P + (2.f * changeVector)) - collisionPoint;
}
template<typename Model>
inline glm::vec3 Object<Model>::getPosition() const
{
	return  glm::vec3(this->globalPosition[3].x, this->globalPosition[3].y, this->globalPosition[3].z);
}
template<typename Model>
inline glm::mat4 Object<Model>::GetGlobalPosition()  const
{
	return glm::scale( globalPosition, scale);
}

template<typename Model>
inline void Object<typename Model>::UpdatePosition(std::chrono::duration<double> deltaT)
{
	globalPosition = glm::translate(globalPosition, moveDirection * (float)deltaT.count());
}
template<typename Model>
inline std::string Object<typename Model>::GetObjectType() const
{
	return objectType;
}
template<typename Model>
inline std::string Object<Model>::GetObjectModel() const
{
	return modelType;
}
;
