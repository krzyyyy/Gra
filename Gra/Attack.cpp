#include "pch.h"
#include "Attack.h"
#include "Character.h"

Attack::Attack(double a): attack(a)
{
}

void Attack::operator()(Character & obj)
{
	if (obj.isDodge())
		return;
	auto armor = obj.getAttrib(attributC::armor);
	double damage = (1 - armor)*attack;
	obj.modifAttr(attributC::live, 0, -damage);
}

void Attack::passRound()
{
}

int Attack::getTime()
{
	return 0;
}


Attack::~Attack()
{
}
