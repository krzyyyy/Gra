#pragma once

#include "ILiveObject.h"
#include "ObjectLogic.h"
#include "Bullet.h"


namespace Logic
{


class EXPORT_OBJECT_LOGIC CollisionInterpreter
{
public:
	void InterpretCollision(std::shared_ptr<ILiveObject>& object1, std::shared_ptr<ILiveObject>& object2);
//private:

	template <typename Object1, typename Object2>
	void operator ()(Object1& object1, Object2& object2);
	
};

template<typename Object1, typename Object2>
inline void CollisionInterpreter::operator ()(Object1& object1, Object2& object2)
{
	std::cout << "Collision interpretation is not implemented" << std::endl;
}
template<>
inline void CollisionInterpreter::operator () <Logic::ObjectLogic, Logic::Bullet>(Logic::ObjectLogic& object1, Logic::Bullet& bullet)
{
	object1.currentLive-=bullet.Damage;
	bullet.Used = true;
}
template<>
inline void CollisionInterpreter::operator () <Logic::ObjectLogic, Logic::ObjectLogic>(Logic::ObjectLogic& object1, Logic::ObjectLogic& object2)
{
	object2.currentLive-= object1.damage;
}

}