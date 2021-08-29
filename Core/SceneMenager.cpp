#include "SceneMenager.h"
#include "Object.h"
#include "ObjectGenerator.h"
#include "IObjectGenerator.h"
#include "LiveObject.h"
#include "..\ObjectLogic\DeleteConditionVisitor.h"
#include "NormalBulletPrototype.h"
//#include <iostream>
//#include <memory>


SceneMenager::SceneMenager():
	enemyMenager()
{
	bullets = std::vector<std::shared_ptr<IObject>>();
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>());
	//objects.emplace_back(std::make_shared< Object<ModelCreators::SphereCreator>>("Bullet"));
	//enemies.emplace_back(std::make_shared<LiveObject< ObjectGenerator< ParametricSphere, ParametricSphere>>>(ObjectGenerator< ParametricSphere, ParametricSphere>("Generator", "CilinderModel"),
	//	Logic::ObjectLogic
	//	{
	//		.maxLive = 120,
	//		.currentLive = 120,
	//		.damage = 5
	//	}
	//));
	//objects.emplace_back(std::make_shared< Object<ModelCreators::CubeCreator>>("Sword"));
	//objects.emplace_back(std::make_shared < ObjectGenerator< ModelCreators::CubeCreator, ModelCreators::SphereCreator>>("Generator"));
	//objects.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CylinderCreator>>>());
	//objects[0]->Scale(glm::vec3(0.5, 0.5, 4));
	//ship = 
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
		enemies[i]->Translate(cubePositions[i]);
	}

	//sword = std::make_shared < Object<ParametricCilinder>>("Model", "SwordModel");
	//sword->Scale(glm::vec3(0.25, 4, 0.25));
	lastTime = std::chrono::steady_clock::now();/*
	generationTimer = Timer(std::chrono::seconds(5));*/
	enemyCreationTimer = Timer(std::chrono::seconds(10));
	enemyMenager.LoadEnemyPrototypes();
}

void SceneMenager::UpdatePosition(std::chrono::duration<double> deltaT)
{

	for (auto& element : enemies)
	{
		element->UpdatePosition(deltaT);
	}
	for (auto& element : bullets)
	{
		element->UpdatePosition(deltaT);
	}
	ship->UpdatePosition(deltaT);
}
void SceneMenager::UpdateScene(ICamera& camera)
{
	auto currentTime = std::chrono::steady_clock::now();
	auto deltaT = currentTime - lastTime;
	lastTime = currentTime;
	UpdatePosition(deltaT);
	for (auto& bullet : bullets)
	{

		std::optional<Match> collision = objectsBouncer.FindCollision(bullet, ship);
		if (auto collisionPointer = collision)
		{
			auto liveBullet = std::dynamic_pointer_cast<Logic::ILiveObject>(bullet);
			auto liveEnemy = std::dynamic_pointer_cast<Logic::ILiveObject>(ship);
			collisionInterpreter.InterpretCollision(liveBullet, liveEnemy);
		}
	}
	for (auto& bullet : bullets)
	{
		for (auto& enemy : enemies)
		{
			std::optional<Match> collision = objectsBouncer.FindCollision(bullet, enemy);
			if (auto collisionPointer = collision)
			{
				auto liveBullet = std::dynamic_pointer_cast<Logic::ILiveObject>(bullet);
				auto liveEnemy = std::dynamic_pointer_cast<Logic::ILiveObject>(enemy);
				collisionInterpreter.InterpretCollision(liveBullet, liveEnemy);
				//collisions.emplace_back(*collisionPointer);
			}
		}
	}
	glm::mat4 shipOrientation = ship->GetGlobalPosition();
	auto shipPosition = Math::GetVectorPosition(shipOrientation);
	enemyCreationTimer.RunEvent(&EnemiesMenager::AddEnemies, enemyMenager, enemies);
	GenerateNewObjects(shipPosition);
	EraseUnusedElements();
	camera.SetCameraPosition(shipOrientation);
	
}

std::vector<std::shared_ptr<IObject>> SceneMenager::GetObjects()
{
	auto allObjects = std::vector<std::shared_ptr<IObject>>();
	for (auto& enemy : enemies)
	{
		allObjects.push_back(enemy);
	}
	for (auto& bullet : bullets)
	{
		allObjects.push_back(bullet);
	}
	allObjects.push_back(ship);
	return allObjects;
}

void SceneMenager::SetShipControler(std::shared_ptr<IShipControler> swordControler)
{
	this->shipControler = std::move(swordControler);
	auto bulletMotionModel = MotionModels::RectilinearMotion(1, glm::vec3(0, 0, 1.));
	auto bulletLiveParams = Logic::Bullet{
		.Damage = 20,
		.Used = false,
	};
	auto bulletPrototype = std::make_unique<NormalBulletPrototype<MotionModels::RectilinearMotion>>(bulletLiveParams, 5);
	auto generatorObject = Object<ParametricSphere, IShipControler&>("Model", "Ship2", *shipControler.get());
	auto objectGenerator = ObjectGenerator(generatorObject, std::move(bulletPrototype), std::chrono::milliseconds(100));
	auto liveParams = Logic::ObjectLogic
	{
		.maxLive = 120,
		.currentLive = 120,
		.damage = 5
	};
	auto liveObject = LiveObject(std::move(objectGenerator), liveParams);
	ship = std::make_shared<decltype(liveObject)>(std::move(liveObject));
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
	glm::vec3 swordPosition = Math::GetVectorPosition(ship->GetGlobalPosition());
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
		if (auto bullet = enemy->generate(posiotion))
		{
			bullets.push_back(*bullet);
		}
	}
	if (auto forwardPoint = shipControler->IsShoting())
	{
		if (auto bullet = ship->generate(*forwardPoint))
		{
			bullets.push_back(*bullet);
		}
	}
	//ship->generate(shipControler->GetNextPosition)
	//std::move(newObjects.begin(), newObjects.end(), std::back_inserter(objects));
}
