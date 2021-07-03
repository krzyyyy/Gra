#include "WeekEnemyPrototype.h"
#include "ObjectGenerator.h"
#include "LiveObject.h"
#include "NormalBulletPrototype.h"
#include <memory>

std::shared_ptr<IObjectGenerator> WeekEnemyPrototype::Clone() const
{
	auto liveTypeBullet = Logic::Bullet{
		.Damage = 20,
		.Used = false,
	};
	//auto motionModel = MotionModels::RectilinearMotion(1, glm::vec3(0, 0, 1));
	auto bulletPrototype = std::make_unique < NormalBulletPrototype<MotionModels::RectilinearMotion>>(liveTypeBullet, 1);
	auto object = Object< ParametricSphere, MotionModels::OrbitalMotion>("Generator", "CilinderModel", MotionModels::OrbitalMotion(0.01, glm::vec3(0, 0, 0), 3, glm::vec3(0, 0, 1)));
	auto objectGenerator = ObjectGenerator(object, std::move(bulletPrototype));
	auto liveParams = Logic::ObjectLogic
	{
		.maxLive = 120,
		.currentLive = 120,
		.damage = 5
	};
	auto liveObject = LiveObject(std::move(objectGenerator), liveParams);
	//enemies.emplace_back(std::make_shared<LiveObject< ObjectGenerator< ParametricSphere, ParametricSphere>>>(ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel"),

	//));
    return std::make_shared<decltype(liveObject)>( std::move(liveObject));
}
