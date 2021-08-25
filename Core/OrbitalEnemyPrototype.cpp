#include "OrbitalEnemyPrototype.h"

#include "MotionModels.h"
#include "ObjectGenerator.h"
#include "NormalBulletPrototype.h"

OrbitalEnemyPrototype::OrbitalEnemyPrototype():
    _angularVelocity(0.),
    _radius(1.),
    _rotationAxis(0. ,0. ,1.)
{
}

OrbitalEnemyPrototype::OrbitalEnemyPrototype(float angularVelocity, float radius, glm::vec3 rotationAxis):
    _angularVelocity(angularVelocity),
    _radius(radius),
    _rotationAxis(rotationAxis)
{
}

std::shared_ptr<IObjectGenerator> OrbitalEnemyPrototype::Clone() const
{
	auto bulletMotionModel = MotionModels::RectilinearMotion(1, glm::vec3(0, 0, 1.));
	auto bulletLiveParams = Logic::Bullet{
		.Damage = 20,
		.Used = false,
	};
	auto bulletPrototype = std::make_unique<NormalBulletPrototype<MotionModels::RectilinearMotion>>(bulletLiveParams, 5);
	auto generatorMotionModel = MotionModels::OrbitalMotion(0.f, glm::vec3(0, 0, 0), _radius, _rotationAxis);
	auto generatorObject = Object<ParametricSphere, MotionModels::OrbitalMotion>("Model", "Ship2", generatorMotionModel);
	auto objectGenerator = ObjectGenerator(generatorObject, std::move( bulletPrototype));
	auto liveParams = Logic::ObjectLogic
	{
		.maxLive = 120,
		.currentLive = 120,
		.damage = 5
	};
	auto liveObject = LiveObject(std::move(objectGenerator), liveParams);
	//enemies.emplace_back(std::make_shared<LiveObject< ObjectGenerator< ParametricSphere, ParametricSphere>>>(ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel"),

	//));
	return std::make_shared<decltype(liveObject)>(std::move(liveObject));
}
