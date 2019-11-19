#include "pch.h"
#include "Skill.h"





Skill::Skill(std::string n, bool iA, bool iM, double c, skillImpl f):
	name(n), isAttack(iA), isMySelf(iM), cost(c), fn(f)
{
}

Skill::Skill():name(""), isAttack(false), isMySelf(false), cost(0.)
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

skillImpl Skill::getFn()
{
	return fn; 
}
