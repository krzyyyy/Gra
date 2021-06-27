#pragma once
#include <iostream>
#include <memory>

#include "LiveObject.h"
#include "Object.h"
#include "IObjectGenerator.h"

template<typename Model, typename GeneratedModel>
class ObjectGenerator: public IObjectGenerator, public Object<Model>
{
public:
	ObjectGenerator() ;
	ObjectGenerator(const ObjectGenerator& object) = default;
	ObjectGenerator(ObjectGenerator&& object) = default;
	ObjectGenerator( std::string objectType_, std::string modelType_);


	std::shared_ptr<IObject> generate(glm::vec3 targetPosition)const;

private:

};

template<typename Model, typename GeneratedModel>
inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator():Object<Model>()
{
}

template<typename Model, typename GeneratedModel>
inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator( std::string objectType_, std::string modelType_): Object<Model>(objectType_, modelType_)
{

}

template<typename Model, typename GeneratedModel>
inline std::shared_ptr<IObject> ObjectGenerator<Model, GeneratedModel>::generate(glm::vec3 targetPosition)const
{
	auto generatorGlobalPosition = Object<Model>::GetGlobalPosition();
	auto generatorPosition = Math::GetVectorPosition(generatorGlobalPosition);
	glm::vec3 targetDirection = targetPosition - generatorPosition;
	glm::vec3 velociti = glm::normalize(targetDirection);
	auto newObject = std::make_shared<LiveObject<Object<GeneratedModel>>>(Object<GeneratedModel>("Bullet", "SphereModel", MoveModels::RectilinearMovement(1, velociti)), Logic::Bullet
		{
			.Damage = 20,
			.Used = false,
		});
	newObject->Translate(generatorPosition );
	return newObject;
}
