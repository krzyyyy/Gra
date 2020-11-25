#pragma once
#include <istream>

#include "Object.h"
#include "Program.h"

class SceneMenager
{
public:
	SceneMenager();
	SceneMenager(const SceneMenager& object) = default;
	SceneMenager(SceneMenager&& object) = default;
	SceneMenager& operator=(const SceneMenager& object) = default;
	SceneMenager& operator=(SceneMenager&& object) = default;
	
	void updateScene();
	void initilizeShaders(const std::pair<std::string, std::string>& objectsShadersNames, const std::pair<std::string, std::string>& swordShadersNames);

private:
	std::vector<std::unique_ptr<IObject>> objects;
	std::unique_ptr<IObject> sword;
	Program objectsProgram;
	Program swordProgram;

};