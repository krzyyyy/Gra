#pragma once
#include <istream>

#include "Object.h"
#include "Program.h"
#include "Camera.h"
//#include "ObjectGenerator.h"

class SceneMenager
{
public:
	SceneMenager();
	SceneMenager(const SceneMenager& object) = default;
	SceneMenager(SceneMenager&& object) = default;
	SceneMenager& operator=(const SceneMenager& object) = default;
	SceneMenager& operator=(SceneMenager&& object) = default;
	
	void updateScene(const Camera& camera);
	void initilizeShaders(const std::pair<std::string, std::string>& objectsShadersNames, const std::pair<std::string, std::string>& swordShadersNames);

private:
	//std::vector<std::unique_ptr<IObjectGenerator>> objectGenerators;
	std::vector<std::unique_ptr<IObject>> objects;
	std::unique_ptr<IObject> sword;
	Program objectsProgram;
	Program swordProgram;
	glm::vec3 swordPosition;

};