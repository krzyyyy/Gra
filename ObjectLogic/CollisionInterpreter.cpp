#include "pch.h"
#include "CollisionInterpreter.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>


void Logic::CollisionInterpreter::InterpretCollision(std::shared_ptr<ILiveObject>& object1, std::shared_ptr<ILiveObject>& object2)
{
		auto liveParams1 = object1->GetLiveParameters();
		auto liveParams2 = object2->GetLiveParameters();
		std::visit(*this, liveParams1, liveParams2);
		object1->SetLiveParameters(liveParams1);
		object2->SetLiveParameters(liveParams2);
		
}
