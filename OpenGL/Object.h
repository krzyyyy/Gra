#pragma once
#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>
#include "ObjectCounter.h"
#include "IObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "RenderObject.h"
#include "IBounceable.h"


template<typename Shape, template<typename> class RenderedObject = RenderObject>
class Object:public ObjectCounter<Object<typename Shape, typename RenderedObject>>, public IObject, public IBounceable
{
public:
	Object();
	Object(std::string objectType_);
	Object(glm::vec3 moveDirection_, std::string objectType_);
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
	// for drawing
	void LoadModel()const;
	//IBounceable methods
	ParametricModel GetParametricModel()const;
	void Bounce(glm::vec3 collisionPoint);
	using ModelType = RenderObject< Shape>;

protected:
	glm::vec3 getPosition()const;
	glm::mat4 globalPosition;
	glm::vec3 moveDirection;
	std::string objectType;

};

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::Object()
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::uniform_real_distribution<double> dist(-1.0, 1.0);
	
	globalPosition = glm::mat4(1.0f);
	moveDirection = glm::vec3(0, 0, 0);//glm::vec3(dist(mt), dist(mt), dist(mt));//
	objectType = "Non";
}

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::Object(std::string objectType_):globalPosition(glm::mat4(1.0f)), moveDirection(glm::vec3(0, 0, 0)), objectType(objectType_)
{
}

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::Object(glm::vec3 moveDirection_, std::string objectType_):moveDirection(moveDirection_), objectType(objectType_)
{
	globalPosition = glm::mat4(1.0f);
}

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::~Object()
{
}

template<typename Shape, template<class> typename RenderedObject>
inline void Object<typename Shape, typename RenderedObject>::Translate(glm::vec3 translateVector)
{
	globalPosition = glm::translate(globalPosition, translateVector);
}

template<typename Shape, template<class> typename RenderedObject>
inline void Object<typename Shape, typename RenderedObject>::Rotate(float angle, glm::vec3 rotateVector)
{
	globalPosition = glm::rotate(globalPosition, angle, rotateVector);
}

template<typename Shape, template<class> typename RenderedObject>
inline void Object<Shape, typename RenderedObject>::Scale(glm::vec3 scaleFactor)
{
	globalPosition = glm::scale(globalPosition, scaleFactor);
}

template<typename Shape, template<class> typename RenderedObject>
void Object<typename Shape, typename RenderedObject>::LoadModel()const
{
	ModelType::getInstance().Load();
}
template<typename Shape, template<class> typename RenderedObject>
inline ParametricModel Object<Shape, typename RenderedObject>::GetParametricModel()const
{
	return Shape::ComputeParametricModel(globalPosition);
}
template<typename Shape, template<class> typename RenderedObject>
inline void Object<Shape, typename RenderedObject>::Bounce(glm::vec3 collisionPoint)
{
	//moveDirection = -moveDirection;
	glm::vec3 P = collisionPoint - moveDirection;
	glm::vec3 centerPosition = getPosition();
	glm::vec3 direction = collisionPoint - centerPosition;
	direction = glm::normalize(direction);
	double D = -((direction.x * P.x) + (direction.y * P.y) + (direction.z * P.z)); 
	double t = -(glm::dot(direction, collisionPoint) + D);//t = -(Axc+Byc+Czc+D)/(A*A + B*B + C*C)
	glm::vec3 Pprojected = glm::vec3((direction.x * t) + collisionPoint.x, (direction.y * t) + collisionPoint.y, (direction.z * t) + collisionPoint.z);
	glm::vec3 changeVector = Pprojected - P; 
	moveDirection = (P + (2.f * changeVector)) - collisionPoint;
}
template<typename Shape, template<class> typename RenderedObject>
inline glm::vec3 Object<Shape, typename RenderedObject>::getPosition() const
{
	return  glm::vec3(this->globalPosition[3].x, this->globalPosition[3].y, this->globalPosition[3].z);
}
template<typename Shape, template<class> typename RenderedObject>
inline glm::mat4 Object<Shape, typename RenderedObject>::GetGlobalPosition()  const
{
	return globalPosition;
}

template<typename Shape, template<class> typename RenderedObject>
inline void Object<typename Shape, typename RenderedObject>::UpdatePosition(std::chrono::duration<double> deltaT)
{
	globalPosition = glm::translate(globalPosition, moveDirection * (float)deltaT.count());
}
template<typename Shape, template<class> typename RenderedObject>
inline std::string Object<typename Shape, typename RenderedObject>::GetObjectType() const
{
	return objectType;
}
;
