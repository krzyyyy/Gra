#include "SceneMenager.h"
#include "ObjectGenerator.h"
#include "IObjectGenerator.h"
#include "LiveObject.h"
#include "..\ObjectLogic\DeleteConditionVisitor.h"
//#include <iostream>
//#include <memory>


SceneMenager::SceneMenager()
{
	bullets = std::vector<std::shared_ptr<IObject>>();
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::SphereCreator>>("Bullet"));
	enemies.emplace_back(std::make_shared<LiveObject< ObjectGenerator< ParametricSphere, ParametricSphere>>>(ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel"),
		Logic::ObjectLogic
		{
			.maxLive = 120,
			.currentLive = 120,
			.damage = 5
		}
	));
	enemies.emplace_back(std::make_shared<LiveObject< ObjectGenerator< ParametricSphere, ParametricSphere>>>(ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel"),
		Logic::ObjectLogic
		{
			.maxLive = 100,
			.currentLive = 20,
			.damage = 5
		}
		));
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
	for (int i = 0; i < enemies.size(); ++i)
	{
		auto object = std::dynamic_pointer_cast<IObject>(enemies[i]);
		if(object)
			object->Translate(cubePositions[i]);
	}

	sword = std::make_shared < Object<ParametricCilinder>>("Sword", "CilinderModel");
	sword->Scale(glm::vec3(0.25, 0.25, 4));
	lastTime = std::chrono::steady_clock::now();
	generationTimer = Timer(std::chrono::seconds(5));
}

void SceneMenager::UpdatePosition(std::chrono::duration<double> deltaT)
{

	for (auto& element : enemies)
	{
		auto object = std::dynamic_pointer_cast<IObject>(element);
		if(object)
			object->UpdatePosition(deltaT);
	}
	for (auto& element : bullets)
	{
		element->UpdatePosition(deltaT);
	}
}
void SceneMenager::UpdateScene(glm::vec3 targetPosition)
{
	auto currentTime = std::chrono::steady_clock::now();
	auto deltaT = currentTime - lastTime;
	lastTime = currentTime;
	UpdatePosition(deltaT);
	for (auto& bullet : bullets)
	{

		std::optional<Match> collision = objectsBouncer.FindCollision(bullet, sword);
		if (auto collisionPointer = collision)
		{
			//collisions.emplace_back(*collisionPointer);
			bullet->BounceReaction(collisionPointer->ColissionPoint);
		}
	}
	for (auto& bullet : bullets)
	{
		for (auto& enemy : enemies)
		{
			auto enemyObject = std::dynamic_pointer_cast<IObject>(enemy);
			if (!enemyObject)
				continue;
			std::optional<Match> collision = objectsBouncer.FindCollision(bullet, enemyObject);
			if (auto collisionPointer = collision)
			{
				auto liveBullet = std::dynamic_pointer_cast<Logic::ILiveObject>(bullet);
				auto liveEnemy = std::dynamic_pointer_cast<Logic::ILiveObject>(enemy);
				collisionInterpreter.InterpretCollision(liveBullet, liveEnemy);
				//collisions.emplace_back(*collisionPointer);
			}
		}
	}
	generationTimer.RunEvent(&SceneMenager::GenerateNewObjects, this, targetPosition);
	EraseUnusedElements();
	
}

std::vector<std::shared_ptr<IObject>> SceneMenager::GetObjects()
{
	auto allObjects = std::vector<std::shared_ptr<IObject>>();
	for (auto& enemy : enemies)
	{
		auto object = std::dynamic_pointer_cast<IObject>(enemy);
		if (!object)
			continue;
		allObjects.push_back(object);
	}
	for (auto& bullet : bullets)
	{
		allObjects.push_back(bullet);
	}
	allObjects.push_back(sword);
	return allObjects;
}

void SceneMenager::SetSwordControler(std::unique_ptr<ISwordControler> swordControler)
{
	this->swordControler = std::move(swordControler);
}



void SceneMenager::EraseUnusedElements()
{
	auto deleteLiveObjectPredicat = [](auto& object)
	{
		std::shared_ptr<Logic::ILiveObject> liveObject = std::dynamic_pointer_cast<Logic::ILiveObject>(object);
		if (!liveObject)
		{
			return false;
		}
		DeleteConditionVisitor deleter;
		auto liveType = liveObject->GetLiveParameters();
		bool toDelete = std::visit(deleter, liveType);
		if (toDelete)
		{
			return true;
		}
		return false;
	};
	glm::vec3 swordPosition = Math::GetVectorPosition(sword->GetGlobalPosition());
	auto deleteSpaceObjectPredicat = [swordPosition](auto& object)
	{
		glm::vec3 objectPosition = Math::GetVectorPosition(object->GetGlobalPosition());
		float distance = glm::length(objectPosition - swordPosition);
		if (distance > radiusOfVisibility)
		{
			return true;
		}
		return false;
	};
	std::erase_if(bullets, deleteLiveObjectPredicat);
	std::erase_if(bullets, deleteSpaceObjectPredicat);
	std::erase_if(enemies, deleteLiveObjectPredicat);

}

void SceneMenager::GenerateNewObjects(glm::vec3 posiotion)
{
	for (const auto& enemy : enemies)
	{
		bullets.push_back(enemy->generate(posiotion));
	}
	//std::move(newObjects.begin(), newObjects.end(), std::back_inserter(objects));
}
