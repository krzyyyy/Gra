#pragma once
#include <istream>

#include "Object.h"
#include "Program.h"
#include "Camera.h"
#include "ObjectGenerator.h"
#include "Timer.h"

class SceneMenager
{
public:
	SceneMenager();
	SceneMenager(const SceneMenager& object) = default;
	SceneMenager(SceneMenager&& object) = default;
	SceneMenager& operator=(const SceneMenager& object) = default;
	SceneMenager& operator=(SceneMenager&& object) = default;
	void RenderScene(const Camera& camera);
	void UpdatePosition(std::chrono::duration<double> deltaT);
	void UpdateScene(const Camera& camera);
	void initilizeShaders(const std::pair<std::string, std::string>& objectsShadersNames, const std::pair<std::string, std::string>& swordShadersNames);

private:
	void GenerateNewObjects(const Camera& camera);
	std::vector<std::shared_ptr<IObject>> objects;
	std::shared_ptr<IObject> sword;
	Program objectsProgram;
	Program swordProgram;
	Program objectGeneratorProgram;
	glm::vec3 swordPosition;
	std::chrono::steady_clock::time_point lastTime;
	Timer generationTimer;
};