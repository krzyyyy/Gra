#include "pch.h"
#include "Character.h"




Character::Character()
{
	Skill _normAttack = Skill("Normal Attack", true, false, 0., [this]() {
		return this->normAtack(); 
	});
	skills.push_back(_normAttack);
	Skill _protect = Skill("Protect", false, true, 0., [this]() {
		return this->protect(); });
	skills.push_back(_protect);
}


bool Character::isDodge()
{
	auto r = ((double)rand() / (RAND_MAX)) + 1;
	auto dodgePro = attributes[attributC::dodge]->getValue();
	if (dodgePro>=r)
		return true;
	return false;
}
bool Character::isDead()
{
	double live = attributes[attributC::live]->getValue();
	return  live <=0.;
}
Effect Character::normAtack()
{
	
	return attributes[attributC::damage]->getValue;
}

Effect Character::protect()
{
	auto eff = [](Character & obj) {
		obj.modifAttr(attributC::armor, 0.5, 0);
	};
	
	return Effect(eff, 1);

}

void Character::init()
{
	for (auto at : attributC()) {
		attributes[at]->init();
	}
	for (auto effect : effects) {
		auto eff = effect.getEffect();
		eff(*this);
	}

}

std::string Character::toString()
{
	std::string str = "";
	for (auto att : attributC()) {
		str += typeid(att).name()+ attributes[att]->toString();
	}
	return str;
}

bool Character::setSkill(int skill)
{
	if(skill>=skills.size())
		return false;
	chosenSkill = skills.begin()+skill;
	return true;
}

void Character::passRound()
{
	for (auto &effect : effects) {
		effect.passRound();
	}
	effects.erase(std::remove_if(effects.begin(), effects.end(), [](auto elem) {
		return elem.getTime() == 0;
	}));
}

Skill Character::getSkill()
{
	return *chosenSkill;
}

double Character::getAttrib(attributC at)
{

	return attributes[at]->getValue;
}

void Character::modifAttr(attributC at, double a, double b)
{
	attributes[at]->modify(a, b);
}

void Character::addEffect(Effect eff)
{
	eff.getEffect()(*this);
	effects.push_back(eff);
}

