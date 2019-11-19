#include "pch.h"
#include "ICharacter.h"




bool ICharacter::isDodge()
{
	auto r = ((double)rand() / (RAND_MAX)) + 1;
	auto dodgePro = attributes[attributC::dodge];
	if (dodgePro>=r)
		return true;
	return false;
}
void ICharacter::normAtack(std::unique_ptr<ICharacter> &obj)
{
	auto damage = attributes[attributC::damage].getValueC();
	auto armor = obj->attributes[attributC::armor].getValueC();
	obj->attributes[attributC::live] -= damage * (1 - armor);
}

bool ICharacter::protect(std::unique_ptr<ICharacter>& obj)
{
	obj->attributes[attributC::armor].addMod(modifierT(0.5, 1));
	return true;
}

std::string ICharacter::toString()
{
	std::string str = "";
	auto allAttributes = std::vector<attributC>({ attributC::live, attributC::concentration, attributC::armor, attributC::damage, attributC::dodge });
	for (auto attr : allAttributes) {
		str += attributes[attr].toString();
	}
	return str;
}

bool ICharacter::setSkill(int skill)
{
	if(skill>=skills.size())
		return false;
	chosenSkill = skills.begin()+skill;
	return true;
}

void ICharacter::passRound()
{
	auto attr = std::vector<attributC>({ attributC::live, attributC::concentration, attributC::armor, attributC::damage, attributC::dodge });
	for (auto at : attr)
		attributes[at].passRound();
}
