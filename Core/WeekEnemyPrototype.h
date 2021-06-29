#pragma once
#include "IEnemyPrototype.h"


class WeekEnemyPrototype: public IEnemyPrototype
{
public:


	// Inherited via IEnemyPrototype
	virtual std::shared_ptr<IObjectGenerator> Clone() override;

};

