#pragma once
#include "ObjectLogic.h"
#include "Bullet.h"

class CollisionInterpreter
{
public:
	template <typename Object1, typename Object2>
	void InterpretCollision(Object1& object1, Object2& object2);
	
};

template<typename Object1, typename Object2>
inline void CollisionInterpreter::InterpretCollision(Object1& object1, Object2& object2)
{
	std::cout << "Collision interpretation is not implemented" << std::endl;
}
template<>
inline void CollisionInterpreter::InterpretCollision<Logic::ObjectLogic, Logic::Bullet>(Logic::ObjectLogic& object1, Logic::Bullet& bullet)
{
	object1.TakeDamage(bullet.Damage);
	bullet.Used = true;
}
template<>
inline void CollisionInterpreter::InterpretCollision<Logic::ObjectLogic, Logic::ObjectLogic>(Logic::ObjectLogic& object1, Logic::ObjectLogic& object2)
{
	object2.TakeDamage(object1.Attack());
}