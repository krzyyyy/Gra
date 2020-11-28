#pragma once
#include <iostream>
#include <memory>

#include "Object.h"
#include "IObjectGenerator.h"

//template<typename Model, typename GeneratedModel>
//class ObjectGenerator: public IObjectGenerator, public Object<Model>
//{
//public:
//	ObjectGenerator() = default;
//	ObjectGenerator(glm::vec3 targetPosition_);
//	std::unique_ptr<IObject> generate(glm::vec3 targetPosition);
//
//private:
//	glm::vec3 targetPosition;
//};
//
//template<typename Model, typename GeneratedModel>
//inline ObjectGenerator<Model, GeneratedModel>::ObjectGenerator(glm::vec3 targetPosition_):targetPosition(targetPosition_)
//{
//}
//
//template<typename Model, typename GeneratedModel>
//inline std::unique_ptr<IObject> ObjectGenerator<Model, GeneratedModel>::generate(glm::vec3 targetPosition)
//{
//	//glm::vec3 targetDirection = targetPosition - glm::vec3(globalPosition[3][0], globalPosition[3][1], globalPosition[3][2]);
//	//return std::make_unique<Object>(targetDirection);
//}
