#pragma once
#include <iostream>
#include <memory>

#include "LiveObject.h"
#include "Object.h"
#include "IObjectGenerator.h"
#include "IBulletPrototype.h"
#include "../SharedUtilities/Timer.h"

template<typename Model, typename MotionModel>
class ObjectGenerator: public IObjectGenerator, public Object<Model, MotionModel>
{
public:
	ObjectGenerator() ;
	ObjectGenerator(const ObjectGenerator& object) = default;
	ObjectGenerator(ObjectGenerator&& object) = default;
	ObjectGenerator(Object<Model, MotionModel> object, std::unique_ptr<IBulletPrototype> bulletPrototype, std::chrono::duration<double> interval);


	std::optional<std::shared_ptr<IObject>> generate(glm::vec3 targetPosition);

private:
	std::unique_ptr<IBulletPrototype> _bulletPrototype;
	Timer timer;
};

template<typename Model, typename MotionModel>
inline ObjectGenerator<Model, MotionModel>::ObjectGenerator():Object<Model, MotionModel>()
{
}

template<typename Model, typename MotionModel>
inline ObjectGenerator<Model, MotionModel>::ObjectGenerator(Object<Model, MotionModel> object,
	std::unique_ptr<IBulletPrototype> bulletPrototype,
	std::chrono::duration<double> interval):
	Object<Model, MotionModel>(object),
	_bulletPrototype(std::move(bulletPrototype)),
	timer(interval)
{

}

template<typename Model, typename MotionModel>
inline std::optional<std::shared_ptr<IObject>> ObjectGenerator<Model, MotionModel>::generate(glm::vec3 targetPosition)
{
	if (!timer.TimePeriodDone())
		return std::nullopt;
	auto globalPosition = ObjectGenerator<Model, MotionModel>::globalPosition;
	auto scale = Object<Model, MotionModel>::scale.x;
	auto objectPosition = Math::GetVectorPosition(globalPosition);
	auto direction = targetPosition - objectPosition;
	direction = (direction / glm::length(direction))* scale;
	
	auto bullet = _bulletPrototype->Clone(objectPosition, targetPosition);
	bullet->Translate(objectPosition+direction);
	
	return bullet;// newObject;
}
