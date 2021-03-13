#include "BounceObject.h"
#include "IBounceable.h"
#include "MathHelperFunctions.h"

std::vector<Match> BounceObjects::FindCollisions(std::vector<std::shared_ptr<IObject>>& objects, const std::shared_ptr<IObject>& sword)
{
    std::shared_ptr<IBounceable> boucableSword = std::dynamic_pointer_cast<IBounceable>(sword);
    if (boucableSword == nullptr)
        throw std::exception{ "Miecz musi byc obiektem odbijalnym" };
    ParametricModel swordModel = boucableSword->GetParametricModel();
    for (auto& object : objects)
    {
        std::shared_ptr<IBounceable> bouncableObject = std::dynamic_pointer_cast<IBounceable>(object);
        if (bouncableObject == nullptr)
            continue;
        ParametricModel objectModel = bouncableObject->GetParametricModel();
        auto colision = std::visit(*this, objectModel, swordModel);
        if (colision.first)
        {
            bouncableObject->Bounce(colision.second);
        }
    }
    return std::vector<Match>();
}

