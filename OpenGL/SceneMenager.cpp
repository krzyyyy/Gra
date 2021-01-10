#include "SceneMenager.h"
#include "RenderObject.h"
#include "CubeCreator.h"
#include "CilinderCreator.h"
#include "SphereCreator.h"
#include "ObjectGenerator.h"
#include "IObjectGenerator.h"
//#include <iostream>
//#include <memory>


SceneMenager::SceneMenager()
{
	objects = std::vector<std::shared_ptr<IObject>>();
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::SphereCreator>>("Bullet"));
	objects.emplace_back(std::make_shared<ObjectGenerator< ModelCreators::CubeCreator, ModelCreators::SphereCreator>>("Generator"));
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>("Sword"));
	//objects.emplace_back(std::make_shared < ObjectGenerator< ModelCreators::CubeCreator, ModelCreators::SphereCreator>>("Generator"));
	//objects.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CylinderCreator>>>());
	//objects[0]->Scale(glm::vec3(0.5, 0.5, 4));
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
		objects[i]->Translate(cubePositions[i]);
	}

	sword = std::make_shared < Object<ModelCreators::SphereCreator>>("Sword");
	lastTime = std::chrono::steady_clock::now();
	generationTimer = Timer(std::chrono::seconds(10));
	renderTimer = Timer(std::chrono::milliseconds(33));
}

void SceneMenager::UpdatePosition(std::chrono::duration<double> deltaT)
{

	for (auto& element : objects)
	{
		element->UpdatePosition(deltaT);
	}
}
void SceneMenager::UpdateScene(const Camera& camera)
{
	auto currentTime = std::chrono::steady_clock::now();
	auto deltaT = currentTime - lastTime;
	lastTime = currentTime;
	UpdatePosition(deltaT);
	objectsBouncer.FindCollisions(objects, sword);
	generationTimer.RunEvent(&SceneMenager::GenerateNewObjects, this, camera);
	//renderTimer.RunEvent(&SceneMenager::RenderScene, this, camera);
	//RenderScene(camera);
}

std::vector<std::shared_ptr<IObject>> SceneMenager::GetObjects()
{
	auto allObjects = objects;
	allObjects.push_back(sword);
	return allObjects;
}



void SceneMenager::GenerateNewObjects(const Camera& camera)
{
	auto newObjects = decltype(objects)();
	for (const auto& object : objects)
	{
		auto generateableObject = std::dynamic_pointer_cast<IObjectGenerator>(object);
		if (generateableObject != nullptr)
		{
			newObjects.push_back(generateableObject->generate(camera.getCameraPos()));
		}
	}
	std::move(newObjects.begin(), newObjects.end(), std::back_inserter(objects));
}
