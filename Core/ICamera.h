#pragma once
#include "../glm/glm.hpp"

class __declspec(dllexport) ICamera
{
public:
	virtual void SetPosition(glm::vec3 position) = 0;
	virtual void SetDiretion(glm::vec3 direction) = 0;
};