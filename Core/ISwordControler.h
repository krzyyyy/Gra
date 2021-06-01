#pragma once
//#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/glm.hpp"


class __declspec (dllexport)  ISwordControler
{
public:
	virtual bool Start() = 0;
	virtual glm::mat4 ActualizePosition() = 0;
	virtual void Close() = 0;
};