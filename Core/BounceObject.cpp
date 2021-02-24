#include "BounceObject.h"
#include "IBounceable.h"
#include "MathHelperFunctions.h"

std::vector<Match> BounceObjects::FindCollisions(std::vector<std::shared_ptr<IObject>>& objects, const std::shared_ptr<IObject>& sword)
{
    std::shared_ptr<IBounceable> boucableSword = std::dynamic_pointer_cast<IBounceable>(sword);
    if (boucableSword == nullptr)
        throw std::exception{ "Miecz musi byc obiektem odbijalnym" };
    ParametricModel swordModel = boucableSword->GetParametricModel();
    //if (!std::holds_alternative<ParametricCilinder>(swordModel))
    //    throw std::exception{ "Miecz musi byc Cilinder" };
    //ParametricCilinder swordSphereModel = std::get<ParametricCilinder>( swordModel);
    for (auto& object : objects)
    {
        std::shared_ptr<IBounceable> bouncableObject = std::dynamic_pointer_cast<IBounceable>(object);
        if (bouncableObject == nullptr)
            continue;
        ParametricModel objectModel = bouncableObject->GetParametricModel();
        auto colision = std::visit(*this, objectModel, swordModel);
        //if (!std::holds_alternative<ParametricSphere>(objectModel))
        //    continue;
        //ParametricSphere objectSphereModel = std::get<ParametricSphere>(objectModel);
        //std::pair<bool, glm::vec3> colision= FindBounce(objectSphereModel, swordSphereModel);
        if (colision.first)
        {
            bouncableObject->Bounce(colision.second);
        }
    }
    return std::vector<Match>();
}

