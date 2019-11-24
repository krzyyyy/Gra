#include "pch.h"
#include "Interaction.h"


bool Interaction::action(std::unique_ptr<Character>& ofenser, std::unique_ptr<Character>& target)
{

	
	if (target->isDodge()) 
		return true;
	// normal atacks
	auto skill = ofenser->getSkill();
	auto effFn = skill.getFn();
	double attack = effFn().getDamage();
	double armor = target->getAttrib(attributC::armor);
	double damage = (1 - armor)*attack;
	target->modifAttr(attributC::live, 0., damage);
	// adding effects
	auto effect = effFn();
	target->addEffect(effect);


	return true;
}



Interaction::Interaction()
{
}

Interaction::~Interaction()
{                                                    
}
           