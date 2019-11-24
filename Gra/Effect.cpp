#include "pch.h"
#include "Effect.h"


void Effect::passRound()
{
	--time;
}

double Effect::getDamage()
{
	return damage;
}

std::function<void(Character&)> Effect::getEffect()
{
	return effect;
}

Effect::Effect(std::function<void(Character&)> e, int t): effect(e), time(t), damage(0.)
{
}

Effect::Effect(double dam):damage(dam), time(0), effect(nullptr)
{
}


Effect::~Effect()
{
}
