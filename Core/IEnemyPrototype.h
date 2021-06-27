#pragma once
#include "IObjectGenerator.h"


class IEnemyPrototype
{
public:
	std::shared_ptr<IObjectGenerator> Clone = 0;

};