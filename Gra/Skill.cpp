#include "pch.h"
#include "Skill.h"


using namespace std;


Skill::Skill(std::string n, bool iA, bool iM, double c, ImplEff f):
	name(n), isAttack(iA), isMySelf(iM), cost(c), fn(f)
{
}

Skill::Skill(const Skill & skill)
{
	this->isAttack = skill.isAttack;
	this->isMySelf = skill.isMySelf;
	this->cost = skill.cost;
	this->name = skill.name;
	this->fn = skill.fn;
}

Skill::Skill()
{
}


Skill::~Skill()
{
}

std::string Skill::getName()
{
	return name;
}

bool Skill::getIsAttack()
{
	return isAttack;
}

bool Skill::getIsMySelf()
{
	return isMySelf;
}

double Skill::getCost()
{
	return cost;
}

ImplEff Skill::getFn()
{
	return fn; 
}
