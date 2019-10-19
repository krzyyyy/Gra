#include "pch.h"
#include "Attributes.h"





Attributes::Attributes(double life_, double concentration_, double armor_, double damage_, double dodge_):
						life(life_), concentration(concentration_), armor(armor_), damage(damage_), dodge(dodge_)
{

}

Attributes::~Attributes()
{
}

void Attributes::passRound()
{
	//decrement each time
	if (lifeT > 0) --lifeT;
	if (concentrationT > 0) --concentrationT;
	if (armorT > 0) --armorT;
	if (damageT > 0) --damageT;
	if (dodgeT > 0) --dodgeT;
	//modificators as 0 
	if (lifeT == 0)lifeM = 0;
	if (concentrationT == 0)concentrationM = 0;
	if (armorT == 0)armorM = 0;
	if (damageT == 0)damageM = 0;
	if (dodgeT == 0)dodgeM = 0;
}

