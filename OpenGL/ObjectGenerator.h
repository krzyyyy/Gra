#pragma once
#include <iostream>
#include <memory>

#include "Object.h"
#include "IObjectGenerator.h"

template<typename Model, typename GeneratedModel>
class ObjectGenerator: public IObjectGenerator, public Object<Model>
{
public:
	ObjectGenerator() ;
	ObjectGenerator(glm::vec3 targetPosition_);
	std::shared_ptr<IObject> generate(glm::vec3 targetPosition)const;

private:
	glm::vec3 targetPosition;
};

template<typename Model, typename GeneratedModel>
inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator():targetPosition()
{
}

template<typename Model, typename GeneratedModel>
inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator(glm::vec3 targetPosition_):targetPosition(targetPosition_)
{
}

template<typename Model, typename GeneratedModel>
inline std::shared_ptr<IObject> ObjectGenerator<Model, GeneratedModel>::generate(glm::vec3 targetPosition)const
{
	glm::vec3 targetDirection = targetPosition - glm::vec3(0, 0, 0);
	glm::vec3 velociti = glm::normalize(targetDirection);
	//velociti *= 0.1;
	return std::make_shared<Object<GeneratedModel>>(velociti);
}
