#include "pch.h"
#include "Effect.h"


void Effect::passRound()
{
	--time;
}

std::function<void(Character&)> Effect::getEffect()
{
	return effect;
}

Effect::Effect(std::function<void(Character&)> &e): effect(e)
{
}


Effect::~Effect()
{
}
