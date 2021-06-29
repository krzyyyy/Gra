#pragma once
#include "IEnemyPrototype.h"
#include "Timer.h"
#include <stack>

class EnemiesMenager
{
public:
	EnemiesMenager();
	void LoadEnemyPrototypes();
	void AddEnemies(std::vector<std::shared_ptr<IObjectGenerator>>& enemies);
	bool IsEmpty();

private:
	glm::vec3 RandPosition();
	std::stack<std::unique_ptr< IEnemyPrototype>> enemiesPrototype;
};

