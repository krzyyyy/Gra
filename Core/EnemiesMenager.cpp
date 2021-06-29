#include "EnemiesMenager.h"
#include "WeekEnemyPrototype.h"
#include <random>

EnemiesMenager::EnemiesMenager()
{
}



void EnemiesMenager::LoadEnemyPrototypes()
{
	enemiesPrototype.push(
		std::make_unique<WeekEnemyPrototype>(WeekEnemyPrototype())
	);
	enemiesPrototype.push(
		std::make_unique<WeekEnemyPrototype>(WeekEnemyPrototype())
	);
	enemiesPrototype.push(
		std::make_unique<WeekEnemyPrototype>(WeekEnemyPrototype())
	);
}



void EnemiesMenager::AddEnemies(std::vector<std::shared_ptr<IObjectGenerator>>& enemies)
{
	if (enemiesPrototype.empty())
	{
		return;
	}
	auto enemy = enemiesPrototype.top()->Clone();
	enemy->Translate(RandPosition());
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

