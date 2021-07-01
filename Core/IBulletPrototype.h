#pragma once
#include "IObject.h"

class IBulletPrototype
{
public :
	virtual std::shared_ptr<IObject> Clone() const = 0;
};