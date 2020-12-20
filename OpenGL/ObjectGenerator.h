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
	ObjectGenerator(const ObjectGenerator& object) = default;
	ObjectGenerator(ObjectGenerator&& object) = default;
	ObjectGenerator( std::string objectType_);


	std::shared_ptr<IObject> generate(glm::vec3 targetPosition)const;

private:

};

template<typename Model, typename GeneratedModel>
inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator():Object<Model>()
{
}

template<typename Model, typename GeneratedModel>
inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator( std::string objectType_): Object<Model>(objectType_)
{
}

template<typename Model, typename GeneratedModel>
inline std::shared_ptr<IObject> ObjectGenerator<Model, GeneratedModel>::generate(glm::vec3 targetPosition)const
{
	auto generatorPosition = glm::vec3(this->globalPosition[3].x, this->globalPosition[3].y, this->globalPosition[3].z);
	glm::vec3 targetDirection = targetPosition - generatorPosition;
	glm::vec3 velociti = glm::normalize(targetDirection);
	auto newObject = std::make_shared<Object<GeneratedModel>>(velociti, "Bullet");
	newObject->Translate(generatorPosition);
	return newObject;
}
