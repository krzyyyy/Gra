#include "EnemiesMenager.h"
#include "WeekEnemyPrototype.h"
#include "OrbitalEnemyPrototype.h"
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

bool EnemiesMenager::IsEmpty()
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

