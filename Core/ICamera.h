#pragma once
#include "../glm/glm.hpp"

class __declspec(dllexport) ICamera
{
public:
	virtual void SetCameraPosition(glm::mat4 objectOrientation) = 0;
};