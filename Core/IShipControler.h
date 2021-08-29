#pragma once
//#include "../glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <chrono>
#include "../glm/glm.hpp"
#include "ICamera.h"


class __declspec (dllexport)  IShipControler
{
public:
	virtual void GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition) = 0;
	virtual glm::vec3 GetNextDirection() const = 0;
	template<typename Model>
	void BounceObject(const Model& model, glm::vec3 colisionPoint) {};
	//virtual void SetCameraParameters(ICamera& camera) const = 0;
	virtual std::optional<glm::vec3> IsShoting() = 0;

	
};