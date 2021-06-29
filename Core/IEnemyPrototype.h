#pragma once
#include "IObjectGenerator.h"


class IEnemyPrototype
{
public:
	virtual std::shared_ptr<IObjectGenerator> Clone() = 0;

};