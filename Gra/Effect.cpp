#include "pch.h"
#include "Effect.h"
#include "Character.h"


using namespace std;

Effect::Effect()
{
}

void Effect::passRound()
{
	--time;
}



std::function<void(Character&)> Effect::getEffectFn()
{
	return effect;
}

Effect::Effect(std::function<void(Character&)> e, int t): effect(e), time(t)
{
}

void Effect::operator()(Character & obj)
{
	effect(obj);
	obj.addEffect(make_unique<Effect>(*this));
}



Effect::~Effect()
{
}
