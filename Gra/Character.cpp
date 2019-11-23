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

bool Character::action(std::unique_ptr<Character>& obj)
{
	if (obj->isDodge()) return false;
	auto fn = chosenSkill->getFn();
	//fn( obj);
	attributes[attributC::concentration] -= chosenSkill->getCost();
	return true;
}

bool Character::isDodge()
{
	auto r = ((double)rand() / (RAND_MAX)) + 1;
	auto dodgePro = attributes[attributC::dodge];
	if (dodgePro>=r)
		return true;
	return false;
}
double Character::normAtack()
{
	return attributes[attributC::damage].getValueC();
}

double Character::protect()
{
	this->attributes[attributC::armor].addMod(modifierT(0.5, 1));
	return 0.;
}

std::string Character::toString()
{
	std::string str = "";
	auto allAttributes = std::vector<attributC>({ attributC::live, attributC::concentration, attributC::armor, attributC::damage, attributC::dodge });
	for (auto attr : allAttributes) {
		str += typeid(attr).name()+ attributes[attr].toString();
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
	auto attr = std::vector<attributC>({ attributC::live, attributC::concentration, attributC::armor, attributC::damage, attributC::dodge });
	for (auto at : attr)
		attributes[at].passRound();
}

Skill Character::getSkill()
{
	return *chosenSkill;
}

void Character::setAttributeMod(attributC at, modifierT mod)
{
	attributes[at].addMod(mod);
}

void Character::hurt(double damage)
{
	attributes[attributC::live] -= damage;
}

void Character::distract(double dist)
{
	attributes[attributC::concentration] -= dist;
}
