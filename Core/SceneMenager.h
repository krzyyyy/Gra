#pragma once
#include <istream>

#include "Object.h"
#include "ObjectGenerator.h"
#include "Timer.h"
#include "BounceObject.h"
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
	SceneMenager(SceneMenager&& object) = default;
	SceneMenager& operator=(const SceneMenager& object) = default;
	SceneMenager& operator=(SceneMenager&& object) = default;
	void UpdatePosition(std::chrono::duration<double> deltaT);
	void UpdateScene(glm::vec3 targetPosition);
	std::vector<std::shared_ptr<IObject>> GetObjects();
private:
	void GenerateNewObjects(glm::vec3 posiotion);
	std::vector<std::shared_ptr<IObject>> objects;
	std::shared_ptr<IObject> sword;

	glm::vec3 swordPosition;
	std::chrono::steady_clock::time_point lastTime;
	Timer generationTimer;
	Timer renderTimer;
	BounceObjects objectsBouncer;
};