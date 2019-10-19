#include "pch.h"
#include "Pomurnik.h"
#include "ISkill.h"


Pomurnik::Pomurnik():skill( skills::normAtack)
{
	setLife(200);
	setConcentration(100);
	setDefense(20);
	setDamage(40);
}

bool Pomurnik::attack(ICharacter & obj)
{
	return false;
}

bool Pomurnik::protect()
{
	return false;
}

std::function<void(ICharacter&)> Pomurnik::skillFactory()
{
	return std::function<void(ICharacter&)>();
}


Pomurnik::~Pomurnik()
{
}
