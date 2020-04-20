#include "pch.h"
#include "EffectInteraction.h"


bool EffectInteraction::action(std::unique_ptr<ICharacter>& ofenser, std::unique_ptr<ICharacter>& target)
{
	// adding effects
	auto skill = ofenser->getSkill();
	auto effectFunction = skill.getFn();
	auto gg = effectFunction();
	target->addEffect(skill.getFn()());
	return true;
}

EffectInteraction::EffectInteraction()
{
}


EffectInteraction::~EffectInteraction()
{
}
