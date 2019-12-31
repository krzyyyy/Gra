#include "pch.h"
#include "EffectInteraction.h"


bool EffectInteraction::action(std::unique_ptr<Character>& ofenser, std::unique_ptr<Character>& target)
{
	// adding effects
	auto skill = ofenser->getSkill();
	target->addEffect(skill.getFn()());
	return true;
}

EffectInteraction::EffectInteraction()
{
}


EffectInteraction::~EffectInteraction()
{
}
