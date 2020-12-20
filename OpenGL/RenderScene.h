#pragma once
#include <iostream>
#include <map>
#include "Program.h"
#include "IObject.h"
#include "IObjectGenerator.h"
#include "Camera.h"


class RenderScene
{
public:
	void RenderObjects(const std::vector<std::shared_ptr<IObject>>& objects, const Camera& camera);
	void InitilizeShaders(const std::vector<std::tuple<std::string, std::string, std::string>>& objectsShadersNames);
private:
	std::map<std::string, Program> programs;
};

