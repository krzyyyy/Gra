#include "SceneMenager.h"
#include "RenderObject.h"
#include "CubeCreator.h"
#include "CilinderCreator.h"
#include "ObjectGenerator.h"
//#include <iostream>
//#include <memory>


SceneMenager::SceneMenager()
{
	objects = std::vector<std::unique_ptr<IObject>>();
	objects.emplace_back(std::make_unique< Object<ModelCreators::CubeCreator>>());
	objects.emplace_back(std::make_unique< Object<ModelCreators::CubeCreator>>());
	objects.emplace_back(std::make_unique< Object<ModelCreators::CylinderCreator>>());
	//objects.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>());
	//objects.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CylinderCreator>>>());
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  3.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	};
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->translate(cubePositions[i]);
	}
	sword = std::make_unique < Object<ModelCreators::CylinderCreator>>();
	//objectGenerators.push_back(std::make_unique<ObjectGenerator<)
}
void SceneMenager::updateScene(const Camera& camera)
{
	objectsProgram.setUniform(camera.getViewMatrix(), "view");
	objectsProgram.setUniform(camera.getProjectionMatrix(), "projection");

	for (auto& element : objects)
	{
		element->render(objectsProgram);
	}

	swordProgram.setUniform(camera.getViewMatrix(), "view");
	swordProgram.setUniform(camera.getProjectionMatrix(), "projection");
	sword->render(swordProgram);
}

void SceneMenager::initilizeShaders(const std::pair<std::string, std::string>& objectsShadersNames, const std::pair<std::string, std::string>& swordShadersNames)
{
	if (!(fs::exists(objectsShadersNames.first) && fs::exists(objectsShadersNames.second)))
	{
		std::cout << "I can't load elements shader" << std::endl;
		throw std::exception();
	}
	if (!(fs::exists(swordShadersNames.first) && fs::exists(swordShadersNames.second)))
	{
		std::cout << "I can't load sword shader" << std::endl;
		throw std::exception();
	}
	//objects shaders loading
	objectsProgram.Initialize(objectsShadersNames.first, objectsShadersNames.second);
	objectsProgram.CompileAndLink();
	//sword shaders loading
	swordProgram.Initialize(swordShadersNames.first, swordShadersNames.second);
	swordProgram.CompileAndLink();
}
