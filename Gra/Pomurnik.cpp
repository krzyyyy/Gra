#include "pch.h"
#include "Pomurnik.h"


Pomurnik::Pomurnik():skill( skills::normAtack)
{

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
