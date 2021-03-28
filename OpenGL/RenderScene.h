#pragma once
#include <iostream>
#include <map>
#include "Program.h"
#include "..\Core\IObject.h"
#include "..\Core\LiveObject.h"
#include "IRenderObject.h"
#include "..\ObjectLogic\ILiveObject.h"
#include "Camera.h"


class RenderScene
{
public:
	RenderScene();
	void RenderObjects(const std::vector<std::shared_ptr<IObject>>& objects, const Camera& camera);
	void InitilizeShaders(const std::vector<std::tuple<std::string, std::string, std::string>>& objectsShadersNames);
	void InitializeModels();
	void AddModel(std::string modelName, IRenderObject& model);
private:
	std::map<std::string, Program> programs;
	std::map<std::string, IRenderObject* > models;
	void renderParametersBar(const std::shared_ptr<IObject>& object, const Camera& camera);
	void renderObject(const std::shared_ptr<IObject>& object, const Camera& camera);
};

