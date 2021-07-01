#pragma once
#include "IBulletPrototype.h"
#include "Object.h"
#include "../ObjectLogic/LiveTypes.h"

template<typename MotionType>
class NormalBulletPrototype :
    public IBulletPrototype
{
public:
    NormalBulletPrototype(Logic::Bullet bullet, MotionType motionType);
    void SetLiveObject(Logic::Bullet bullet);
    void SetMotionType(MotionType motionType);
    ~NormalBulletPrototype();
    // Inherited via IBulletPrototype
    virtual std::shared_ptr<IObject> Clone() const override;
private:
    Logic::Bullet _bullet;
    MotionType _motionType;
};

template<typename MotionType>
inline NormalBulletPrototype<MotionType>::NormalBulletPrototype(Logic::Bullet bullet, MotionType motionType):
    _bullet(bullet),
    _motionType(motionType)
{
}

template<typename MotionType>
inline void NormalBulletPrototype<MotionType>::SetLiveObject(Logic::Bullet bullet)
{
    _bullet = bullet;
}

template<typename MotionType>
inline void NormalBulletPrototype<MotionType>::SetMotionType(MotionType motionType)
{
    _motionType = motionType;
}

template<typename MotionType>
inline NormalBulletPrototype<MotionType>::~NormalBulletPrototype()
{
}

template<typename MotionType>
inline std::shared_ptr<IObject> NormalBulletPrototype<MotionType>::Clone() const
{
    auto object = Object<ParametricSphere>("Bullet", "SphereModel", _motionType);
    auto liveObject = LiveObject(object, _bullet);
    return std::make_shared<decltype(liveObject)>(std::move(liveObject));
}
