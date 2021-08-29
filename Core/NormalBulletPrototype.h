#pragma once
#include "IBulletPrototype.h"
#include "Object.h"
#include "../ObjectLogic/LiveTypes.h"

template<typename MotionType>
class NormalBulletPrototype :
    public IBulletPrototype
{
public:
    NormalBulletPrototype(Logic::Bullet bullet, float velocity);
    void SetLiveObject(Logic::Bullet bullet);
    ~NormalBulletPrototype();
    // Inherited via IBulletPrototype
    virtual std::shared_ptr<IObject> Clone(glm::vec3 beginTrajectory, glm::vec3 pointOnTrajectory) const override;
private:
    Logic::Bullet _bullet;
    float _velocity;
};

template<typename MotionType>
inline NormalBulletPrototype<MotionType>::NormalBulletPrototype(Logic::Bullet bullet, float velocity):
    _bullet(bullet),
    _velocity(velocity)
{
}

template<typename MotionType>
inline void NormalBulletPrototype<MotionType>::SetLiveObject(Logic::Bullet bullet)
{
    _bullet = bullet;
}


template<typename MotionType>
inline NormalBulletPrototype<MotionType>::~NormalBulletPrototype()
{
}

template<typename MotionType>
inline std::shared_ptr<IObject> NormalBulletPrototype<MotionType>::Clone(glm::vec3 beginTrajectory, glm::vec3 pointOnTrajectory) const
{
    auto object = Object<ParametricSphere>("Model", "ShotModel", MotionType(beginTrajectory, pointOnTrajectory, _velocity));
    object.Scale(glm::vec3(0.25f, 0.25f, 0.25f));
    auto liveObject = LiveObject(object, _bullet);
    return std::make_shared<decltype(liveObject)>(std::move(liveObject));
}
