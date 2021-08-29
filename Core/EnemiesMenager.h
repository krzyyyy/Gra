#pragma once
#include "IEnemyPrototype.h"
#include <stack>

class EnemiesMenager
{
public:
	EnemiesMenager();
	EnemiesMenager(const EnemiesMenager&) = delete;
	EnemiesMenager(EnemiesMenager&&) = default;
	EnemiesMenager& operator=(const EnemiesMenager&) = delete;
	EnemiesMenager& operator=(EnemiesMenager&&) = default;

	void LoadEnemyPrototypes();
	void AddEnemies(std::vector<std::shared_ptr<IObjectGenerator>>& enemies);
	bool IsEmpty();

private:
	glm::vec3 RandPosition();
	std::stack<std::unique_ptr< IEnemyPrototype>> enemiesPrototype;
};

