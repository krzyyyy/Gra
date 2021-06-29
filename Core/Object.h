#pragma once
#include <iostream>
#include <random>
//#include <opencv2/opencv.hpp>
#include "ObjectCounter.h"
#include "IObject.h"
//#include "glm/gtc/matrix_transform.hpp"
#include "IBounceable.h"
#include "MoveModels.h"




template<typename Model, typename MoveModel = MoveModels::RectilinearMovement>
class Object:public ObjectCounter<Object<typename Model>>, virtual public IObject
{
public:
	Object();
	Object(std::string objectType_, std::string modelType_);
	Object( std::string objectType_, std::string modelType_, MoveModel moveModel_);
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
	void BounceReaction(glm::vec3 collisionPoint) override;

	bool IsMovingAway(const std::shared_ptr<IObject>& object) override;
protected:
	glm::vec3 scale;
	glm::mat4 globalPosition;
	MoveModel moveModel;
	std::string objectType;
	std::string modelType;


	// Inherited via IObject
	virtual void SetGlobalPosition(const glm::mat4& globalPosition) override
	{
		this->globalPosition = globalPosition;
	}

};

template<typename Model, typename MoveModel>
inline Object<typename Model, typename MoveModel>::Object()
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::uniform_real_distribution<double> dist(-1.0, 1.0);
	scale = glm::vec3(1., 1., 1.);
	globalPosition = glm::mat4(1.0f);
	moveModel = MoveModel();
	objectType = "Non";
	modelType = "Non"; 
}

template<typename Model, typename MoveModel>
inline Object<typename Model, typename MoveModel>::Object(std::string objectType_, std::string modelType_):globalPosition(glm::mat4(1.0f)),scale(1., 1., 1.),
moveModel() , objectType(objectType_), modelType(modelType_)
{
}

template<typename Model, typename MoveModel>
inline Object<typename Model, typename MoveModel>::Object(std::string objectType_, std::string modelType_, MoveModel moveModel_):scale(1., 1.,1.),
globalPosition(1.0f), moveModel(moveModel_), objectType(objectType_), modelType(modelType_)
{
}

template<typename Model, typename MoveModel>
inline Object<typename Model, typename MoveModel>::~Object()
{
}

template<typename Model, typename MoveModel>
inline void Object<typename Model, typename MoveModel>::Translate(glm::vec3 translateVector)
{
	globalPosition = glm::translate(globalPosition, translateVector);
}

template<typename Model, typename MoveModel>
inline void Object<typename Model, typename MoveModel>::Rotate(float angle, glm::vec3 rotateVector)
{
	globalPosition = glm::rotate(globalPosition, angle, rotateVector);
}

template<typename Model, typename MoveModel>
inline void Object<Model, typename MoveModel>::Scale(glm::vec3 scaleFactor)
{
	scale = scale * scaleFactor;
}

template<typename Model, typename MoveModel>
inline ParametricModel Object<Model, typename MoveModel>::GetParametricModel()const
{
	return Model::ComputeParametricModel(globalPosition, scale);
}
template<typename Model, typename MoveModel>
inline void Object<Model, typename MoveModel>::BounceReaction(glm::vec3 collisionPoint)
{
	//moveDirection = -moveDirection;
	auto parametricModel = Model::ComputeParametricModel(globalPosition, scale);
	moveModel.BounceObject(parametricModel, collisionPoint);
}
template<typename Model, typename MoveModel>
inline bool Object<Model, typename MoveModel>::IsMovingAway(const std::shared_ptr<IObject>& object)
{
	double epsilon = 0.2;
	glm::mat4 object1GlobalPosition = object->GetGlobalPosition();
	glm::vec3 object1Center  = Math::GetVectorPosition(object1GlobalPosition);
	glm::vec3 difference = object1Center - Math::GetVectorPosition(globalPosition);

	difference = glm::normalize(difference);
	glm::vec3 moveDirection = moveModel.GetNextDirection();
	auto dotProdact = glm::dot(difference, moveDirection);
	auto diff = std::abs(dotProdact - (-1));
	return diff < epsilon;
}
template<typename Model, typename MoveModel>
inline glm::mat4 Object<Model, typename MoveModel>::GetGlobalPosition()  const
{
	return glm::scale( globalPosition, scale);
}

template<typename Model, typename MoveModel>
inline void Object<typename Model, typename MoveModel>::UpdatePosition(std::chrono::duration<double> deltaT)
{
	moveModel.GetNextPosition(deltaT, globalPosition);
}
template<typename Model, typename MoveModel>
inline std::string Object<typename Model, typename MoveModel>::GetObjectType() const
{
	return objectType;
}
template<typename Model, typename MoveModel>
inline std::string Object<Model, typename MoveModel>::GetObjectModel() const
{
	return modelType;
}
;