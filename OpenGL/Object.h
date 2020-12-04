#pragma once
#include <iostream>
#include <random>
#include "Program.h"
#include <opencv2/opencv.hpp>
#include "ObjectCounter.h"
#include "IObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "RenderObject.h"


template<typename Shape, template<typename> class RenderedObject = RenderObject>
class Object:public ObjectCounter<Object<typename Shape, typename RenderedObject>>, public IObject
{
public:
	Object();
	Object(glm::vec3 moveDirection_);
	~Object();
	void translate(glm::vec3 translateVector);
	void rotate(float angle, glm::vec3 rotateVector);
	void render(const Program& program);

	using ModelType = RenderObject< Shape>;

protected:
	void updatePosition();
	glm::mat4 globalPosition;
	glm::vec3 moveDirection;
	float velocity;

};

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::Object():velocity(0.0)
{
	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::uniform_real_distribution<double> dist(-1.0, 1.0);
	
	globalPosition = glm::mat4(1.0f);
	moveDirection = glm::vec3(0, 0, 0);//glm::vec3(dist(mt), dist(mt), dist(mt));//
}

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::Object(glm::vec3 moveDirection_):moveDirection(moveDirection_), velocity(0.1)
{
	globalPosition = glm::mat4(1.0f);
}

template<typename Shape, template<class> typename RenderedObject>
inline Object<typename Shape, typename RenderedObject>::~Object()
{
}

template<typename Shape, template<class> typename RenderedObject>
inline void Object<typename Shape, typename RenderedObject>::translate(glm::vec3 translateVector)
{
	globalPosition = glm::translate(globalPosition, translateVector);
}

template<typename Shape, template<class> typename RenderedObject>
inline void Object<typename Shape, typename RenderedObject>::rotate(float angle, glm::vec3 rotateVector)
{
	globalPosition = glm::rotate(globalPosition, angle, rotateVector);
}

template<typename Shape, template<class> typename RenderedObject>
void Object<typename Shape, typename RenderedObject>::render(const Program& program)
{
	//program.useProgram();
	program.setUniform(globalPosition, "model");
	
	updatePosition();

	ModelType::getInstance().Render();

};
template<typename Shape, template<class> typename RenderedObject>
inline void Object<typename Shape, typename RenderedObject>::updatePosition()
{
	globalPosition = glm::translate(globalPosition, moveDirection * velocity);
};
