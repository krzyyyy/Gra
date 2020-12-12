#include "SceneMenager.h"
#include "RenderObject.h"
#include "CubeCreator.h"
#include "CilinderCreator.h"
#include "ObjectGenerator.h"
#include "IObjectGenerator.h"
//#include <iostream>
//#include <memory>


SceneMenager::SceneMenager()
{
	objects = std::vector<std::shared_ptr<IObject>>();
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	objects.emplace_back(std::make_shared< Object<ModelCreators::CylinderCreator>>());
	objects.emplace_back(std::make_unique<ObjectGenerator< ModelCreators::CubeCreator, ModelCreators::CylinderCreator>>());
	
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

	sword = std::make_shared < Object<ModelCreators::CylinderCreator>>();
	lastTime = std::chrono::steady_clock::now();
}
void SceneMenager::RenderScene(const Camera& camera)
{
	objectsProgram.useProgram();
	objectsProgram.setUniform(camera.getViewMatrix(), "view");
	objectsProgram.setUniform(camera.getProjectionMatrix(), "projection");
	for (const auto& element : objects)
	{
		auto objectPointer = std::dynamic_pointer_cast<IObjectGenerator>(element);
		if (!objectPointer)
			objectsProgram.Render(element);

	}

	swordProgram.useProgram();
	swordProgram.setUniform(camera.getViewMatrix(), "view");
	swordProgram.setUniform(camera.getProjectionMatrix(), "projection");
	swordProgram.Render(sword);
	objectGeneratorProgram.useProgram();
	objectGeneratorProgram.setUniform(camera.getViewMatrix(), "view");
	objectGeneratorProgram.setUniform(camera.getProjectionMatrix(), "projection");
	objectGeneratorProgram.setUniform(glm::vec3(0.9, 0.2, 0.1), "color");

	for (const auto& element : objects)
	{
		auto objectPointer = std::dynamic_pointer_cast<IObjectGenerator>(element);
		if (objectPointer)
		{
			objectGeneratorProgram.Render(element);
		}
	}
}
void SceneMenager::UpdatePosition(std::chrono::duration<double> deltaT)
{

	for (auto& element : objects)
	{
		element->updatePosition(deltaT);
	}
}
void SceneMenager::UpdateScene(const Camera& camera)
{
	auto currentTime = std::chrono::steady_clock::now();
	auto deltaT = currentTime - lastTime;
	lastTime = currentTime;

	RenderScene(camera);
}

void SceneMenager::initilizeShaders(const std::pair<std::string, std::string>& objectsShadersNames, const std::pair<std::string, std::string>& swordShadersNames)
{
	auto objectGeneratorShadersNames = std::make_pair(objectsShadersNames.first, "ObjectGeneratorShader.glsl");
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
	if (!(fs::exists(objectGeneratorShadersNames.first) && fs::exists(objectGeneratorShadersNames.second)))
	{
		std::cout << "I can't load objectGenerator shader" << std::endl;
		throw std::exception();
	}
	//objects shaders loading
	objectsProgram.Initialize(objectsShadersNames.first, objectsShadersNames.second);
	objectsProgram.CompileAndLink();
	//sword shaders loading
	swordProgram.Initialize(swordShadersNames.first, swordShadersNames.second);
	swordProgram.CompileAndLink();

	//objectsGenerator shaders loading
	objectGeneratorProgram.Initialize(objectGeneratorShadersNames.first, objectGeneratorShadersNames.second);
	objectGeneratorProgram.CompileAndLink();
	//
}
