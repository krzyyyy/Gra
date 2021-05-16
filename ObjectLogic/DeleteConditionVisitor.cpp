#include "pch.h"
#include "DeleteConditionVisitor.h"

bool DeleteConditionVisitor::operator()(Logic::ObjectLogic& object)
{
	if (object.currentLive <= 0.)
	{
		return true;
	}
	return false;
}

bool DeleteConditionVisitor::operator()(Logic::Bullet& bullet)
{
	if (bullet.Used)
	{
		return true;
	}
	return false;
}
