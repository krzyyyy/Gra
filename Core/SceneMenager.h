#pragma once
#include <istream>

//#include "Object.h"
#include "IObjectGenerator.h"
#include "ObjectGenerator.h"
#include "Timer.h"
#include "BounceObject.h"
#include "ISwordControler.h"
#include "EnemiesMenager.h"
#ifdef EXPORT_FLAG
#define EXPORT_MODULES __declspec(dllexport)
#else
#define EXPORT_MODULES __declspec(dllimport)
#endif
class EXPORT_MODULES SceneMenager
{
public:
	SceneMenager();
	SceneMenager(const SceneMenager& object) = default;
	SceneMenager(SceneMenager&& object) noexcept = default;
	SceneMenager& operator=(const SceneMenager& object) = default;
	SceneMenager& operator=(SceneMenager&& object) = default;
	void UpdateScene(glm::vec3 targetPosition);
	std::vector<std::shared_ptr<IObject>> GetObjects();

	void SetSwordControler(std::unique_ptr<ISwordControler> swordControler);
private:
	void EraseUnusedElements();
	void GenerateNewObjects(glm::vec3 posiotion);

	void UpdatePosition(std::chrono::duration<double> deltaT);
	//objects
	std::vector<std::shared_ptr<IObject>> bullets;
	std::vector<std::shared_ptr<IObjectGenerator>> enemies;

	std::shared_ptr<IObject> sword;
	std::unique_ptr<ISwordControler> swordControler;

	std::chrono::steady_clock::time_point lastTime;
	Timer generationTimer;
	Timer enemyCreationTimer;
	BounceObjects objectsBouncer;
	Logic::CollisionInterpreter collisionInterpreter;
	EnemiesMenager enemyMenager;
	const static int radiusOfVisibility = 30;
};