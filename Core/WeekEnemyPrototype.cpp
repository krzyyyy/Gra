#include "WeekEnemyPrototype.h"
#include "ObjectGenerator.h"
#include "LiveObject.h"

std::shared_ptr<IObjectGenerator> WeekEnemyPrototype::Clone()
{
	auto objectGenerator = ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel");
	auto liveParams = Logic::ObjectLogic
	{
		.maxLive = 120,
		.currentLive = 120,
		.damage = 5
	};
	auto liveObject = LiveObject(objectGenerator, liveParams);
	//enemies.emplace_back(std::make_shared<LiveObject< ObjectGenerator< ParametricSphere, ParametricSphere>>>(ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel"),

	//));
    return std::make_shared<decltype(liveObject)>( std::move(liveObject));
}
