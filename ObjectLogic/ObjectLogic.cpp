#include "pch.h"
#include "ObjectLogic.h"


Logic::ObjectLogic::ObjectLogic() :
    maxLive(1), currentLive(1), damage(1)
{

}

Logic::ObjectLogic::ObjectLogic(double maxLive_, double currentLive_, double damage_):
    maxLive(maxLive_), currentLive(currentLive_), damage(damage_)
{
}

void Logic::ObjectLogic::TakeDamage(double value)
{
    currentLive -= value;
}

double Logic::ObjectLogic::MaxLive() const
{
    return maxLive;
}

double Logic::ObjectLogic::CurrentLive() const
{
    return currentLive;
}

double Logic::ObjectLogic::Attack() const
{
    return damage;
}

bool Logic::ObjectLogic::IsDead() const
{
    return currentLive <= 0.;
}

