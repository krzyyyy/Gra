#include "BounceObject.h"
#include "IBounceable.h"

std::vector<Match> BounceObjects::FindCollisions(std::vector<std::shared_ptr<IObject>>& objects, const std::shared_ptr<IObject>& sword)
{
    std::shared_ptr<IBounceable> boucableSword = std::dynamic_pointer_cast<IBounceable>(sword);
    if (boucableSword == nullptr)
        throw std::exception{ "Miecz musi byc obiektem odbijalnym" };
    ParametricModel swordModel = boucableSword->GetParametricModel();
    if (!std::holds_alternative<ParametricSphere>(swordModel))
        throw std::exception{ "Miecz musi byc sfera" };
    ParametricSphere swordSphereModel = std::get<ParametricSphere>( swordModel);
    for (auto& object : objects)
    {
        std::shared_ptr<IBounceable> bouncableObject = std::dynamic_pointer_cast<IBounceable>(object);
        if (bouncableObject == nullptr)
            continue;
        ParametricModel objectModel = bouncableObject->GetParametricModel();
        if (!std::holds_alternative<ParametricSphere>(objectModel))
            continue;
        ParametricSphere objectSphereModel = std::get<ParametricSphere>(objectModel);
        std::pair<bool, glm::vec3> colision= FindBounce(objectSphereModel, swordSphereModel);
        if (colision.first)
        {
            bouncableObject->Bounce(colision.second);
        }
    }
    return std::vector<Match>();
}

std::pair<bool,glm::vec3> BounceObjects::FindBounce(ParametricSphere object1, ParametricSphere object2)
{
    glm::vec3 difference = object2.Center - object1.Center;
    glm::vec3 direction = glm::normalize(difference);
    
    if (glm::length(difference) > object1.R + object2.R)
    {
        return std::make_pair(false, glm::vec3(0,0,0));
    }
    glm::vec3 colisionPoint = object1.Center + (direction * float(object1.R));
    return std::make_pair(true, colisionPoint);
}
