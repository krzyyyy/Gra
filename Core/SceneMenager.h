#pragma once
#include <istream>

//#include "Object.h"
#include "IObjectGenerator.h"
#include "ObjectGenerator.h"
#include "Timer.h"
#include "BounceObject.h"
#include "IShipControler.h"
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
	void UpdateScene(ICamera& camera);
	std::vector<std::shared_ptr<IObject>> GetObjects();

	void SetShipControler(std::unique_ptr<IShipControler> swordControler);
private:
	void EraseUnusedElements();
	void GenerateNewObjects(glm::vec3 posiotion);

	void UpdatePosition(std::chrono::duration<double> deltaT);
	//objects
	std::vector<std::shared_ptr<IObject>> bullets;
	std::vector<std::shared_ptr<IObjectGenerator>> enemies;

	std::shared_ptr<IObjectGenerator> ship;
	std::unique_ptr<IShipControler> shipControler;

	std::chrono::steady_clock::time_point lastTime;
	Timer generationTimer;
	Timer enemyCreationTimer;
	BounceObjects objectsBouncer;
	Logic::CollisionInterpreter collisionInterpreter;
	EnemiesMenager enemyMenager;
	const static int radiusOfVisibility = 30;
};