#include "BounceObject.h"
#include "IBounceable.h"
#include "MathHelperFunctions.h"
#include "..\ObjectLogic\ILiveObject.h"

std::optional<Match> BounceObjects::FindCollision(std::shared_ptr<IObject>& object1, const std::shared_ptr<IObject>& object2)
{

    ParametricModel swordModel = object2->GetParametricModel();
	ParametricModel objectModel = object1->GetParametricModel();
    if (object1->IsMovingAway(object2))
    {
        return std::nullopt;
    }
	auto colision = std::visit(*this, objectModel, swordModel);
	if (colision.first)
	{
        //object->Bounce(colision.second);
		return Match{ .QueryIdx = object1, .TrainIdx = object2, .ColissionPoint = colision.second };
        
	}
    return std::nullopt;
    //for (auto obejectIterator = objects.cbegin(); obejectIterator != objects.cend(); ++obejectIterator)
    //{
    //    std::shared_ptr<IBounceable> bounceObject = std::dynamic_pointer_cast<IBounceable>(*obejectIterator);
    //    if (!bounceObject)
    //        continue;
    //    ParametricModel objectParametricModel = bounceObject->GetParametricModel();
    //    for (auto obejectIterator2 = obejectIterator+1; obejectIterator2 != objects.cend(); ++obejectIterator2)
    //    {
    //        std::shared_ptr<IBounceable> bounceObject2 = std::dynamic_pointer_cast<IBounceable>(*obejectIterator2);
    //        if (!bounceObject2)
    //            continue;
    //        ParametricModel object2ParametricModel = bounceObject2->GetParametricModel();
    //        auto colision = std::visit(*this, objectParametricModel, object2ParametricModel);
    //        if (colision.first)
    //        {
    //            //collisions.emplace_back(Match{ .QueryIdx = object, .TrainIdx = sword, .ColissionPoint = colision.second });
    //            //bouncableObject->Bounce(colision.second);
    //        }
    //    }
    //}
    //return collisions;
}

void BounceObjects::InterpretCollisions(const std::vector<Match>& collisions)
{
    for (const auto& collision : collisions)
    {
        auto liveObject1 = std::dynamic_pointer_cast<Logic::ILiveObject>(collision.QueryIdx);
        auto liveObject2 = std::dynamic_pointer_cast<Logic::ILiveObject>(collision.TrainIdx);
        if (liveObject1 && liveObject2)
        {
            collisionInterpreter.InterpretCollision(liveObject1, liveObject2);
        }
    }
}

