#pragma once
//#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/glm.hpp"


class ISwordControler
{
public:
	virtual bool Initialize() = 0;
	virtual glm::mat4 ActualizePosition() = 0;
};