#include "pch.h"
#include "Interaction.h"


bool Interaction::action(std::unique_ptr<Character>& ofenser, std::unique_ptr<Character>& target)
{

	
	if (target->isDodge()) 
		return true;
	auto skill = ofenser->getSkill();
	auto armor = target->getAttribute(attributC::armor);
	double damage = (1 - armor.getValueC)*skill;
	target->hurt(damage);
	return true;
}



Interaction::Interaction()
{
}

Interaction::~Interaction()
{                                                    
}
           