#include "EnemiesMenager.h"
#include "WeekEnemyPrototype.h"
#include "OrbitalEnemyPrototype.h"
#include "LiveObject.h"
#include "Object.h"
#include <random>

EnemiesMenager::EnemiesMenager():
	enemiesPrototype()
{
}



void EnemiesMenager::LoadEnemyPrototypes()
{
	enemiesPrototype.push(
		std::make_unique<OrbitalEnemyPrototype>(OrbitalEnemyPrototype(1, 3, glm::vec3(0, 0, 1.)))
	);
	enemiesPrototype.push(
		std::make_unique<OrbitalEnemyPrototype>(OrbitalEnemyPrototype(0.5, 6, glm::vec3(0, 1, 0)))
	);
	//enemiesPrototype.push(
	//	std::make_unique<WeekEnemyPrototype>(WeekEnemyPrototype())
	//);
}

void EnemiesMenager::InitializeScene(std::vector<std::shared_ptr<IObject>>& objects)
{
	for (int i = 1; i < 20; ++i)
	{
		auto orbitalModel = MotionModels::OrbitalMotion(i*0.01f + 0.05f, glm::vec3(), 5, glm::normalize(glm::vec3((i* 123424)% 10, (i * 345345)% 10, (i* 8678678)% 10)));
		auto bullet = Logic::Bullet{ .Damage = 15, .Used = false };
		auto object = Object<ParametricSphere, MotionModels::OrbitalMotion>("Model", "AsteroidModel", orbitalModel);
		object.Scale(glm::vec3(0.25f, 0.25f, 0.25f));
		auto liveObject = LiveObject(object, bullet);
		objects.push_back(std::make_shared<decltype(liveObject)>(std::move(liveObject)));
	}
	auto mainObjectMotionModel = MotionModels::RectilinearMotion(0.f, glm::vec3(0.f, 0.f, 0.f));
	auto mainObjectBullet = Logic::Bullet{ .Damage = 100, .Used = false };
	auto mainObject = Object<ParametricSphere, MotionModels::RectilinearMotion>("Model", "ShotModel", mainObjectMotionModel);
	mainObject.Scale(glm::vec3(3.f, 3.f, 3.f));
	auto mainLiveObject = LiveObject(mainObject, mainObjectBullet);
	objects.push_back(std::make_shared<decltype(mainLiveObject)>(std::move(mainLiveObject)));

}



void EnemiesMenager::AddEnemies(std::vector<std::shared_ptr<IObjectGenerator>>& enemies)
{
	if (enemiesPrototype.empty())
	{
		return;
	}
	auto enemy = enemiesPrototype.top()->Clone();
	enemy->Translate(glm::vec3(1, 1, 1));
	enemies.push_back(enemy);
	enemiesPrototype.pop();
}

bool EnemiesMenager::IsEmpty() const
{
	return enemiesPrototype.empty();
}

glm::vec3 EnemiesMenager::RandPosition()
{
	const int range_from = -10;
	const int range_to = 10;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	return glm::vec3(distr(generator), distr(generator), distr(generator));
}

