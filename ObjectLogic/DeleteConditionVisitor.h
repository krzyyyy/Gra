#pragma once
#include "LiveTypes.h"
class EXPORT_OBJECT_LOGIC DeleteConditionVisitor
{
public:
	bool operator()(Logic::ObjectLogic& object);
	bool operator()(Logic::Bullet& bullet);

};

