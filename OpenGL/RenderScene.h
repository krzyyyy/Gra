#pragma once
#include <iostream>
#include <map>
#include "Program.h"
#include "..\Core\IObject.h"
#include "IRenderObject.h"
#include "Camera.h"


class RenderScene
{
public:
	RenderScene();
	void RenderObjects(const std::vector<std::shared_ptr<IObject>>& objects, const Camera& camera);
	void InitilizeShaders(const std::vector<std::tuple<std::string, std::string, std::string>>& objectsShadersNames);
	void AddModel(std::string modelName, IRenderObject& model);
private:
	std::map<std::string, Program> programs;
	std::map<std::string, IRenderObject* > models;
};

