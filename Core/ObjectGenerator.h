#pragma once
#include <iostream>
#include <memory>

#include "LiveObject.h"
#include "Object.h"
#include "IObjectGenerator.h"
#include "IBulletPrototype.h"

template<typename Model, typename MotionModel>
class ObjectGenerator: public IObjectGenerator, public Object<Model, MotionModel>
{
public:
	ObjectGenerator() ;
	ObjectGenerator(const ObjectGenerator& object) = default;
	ObjectGenerator(ObjectGenerator&& object) = default;
	ObjectGenerator(Object<Model, MotionModel> object, std::unique_ptr<IBulletPrototype> bulletPrototype);


	std::shared_ptr<IObject> generate(glm::vec3 targetPosition)const;

private:
	std::unique_ptr<IBulletPrototype> _bulletPrototype;
};

template<typename Model, typename MotionModel>
inline ObjectGenerator<Model, MotionModel>::ObjectGenerator():Object<Model, MotionModel>()
{
}

template<typename Model, typename MotionModel>
inline ObjectGenerator<Model, MotionModel>::ObjectGenerator(Object<Model, MotionModel> object,
	std::unique_ptr<IBulletPrototype> bulletPrototype):
	Object<Model, MotionModel>(object),
	_bulletPrototype(std::move(bulletPrototype))
{

}

template<typename Model, typename MotionModel>
inline std::shared_ptr<IObject> ObjectGenerator<Model, MotionModel>::generate(glm::vec3 targetPosition)const
{
	auto globalPosition = ObjectGenerator<Model, MotionModel>::globalPosition;
	auto scale = Object<Model, MotionModel>::scale.x;
	auto objectPosition = Math::GetVectorPosition(globalPosition);
	auto direction = targetPosition - objectPosition;
	direction = (direction / glm::length(direction))* scale;
	
	auto bullet = _bulletPrototype->Clone(objectPosition, targetPosition);
	bullet->Translate(objectPosition+direction);
	
	return bullet;// newObject;
}
