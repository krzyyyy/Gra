#include "pch.h"
#include "ICharacter.h"




bool ICharacter::isDodge()
{
	auto r = ((double)rand() / (RAND_MAX)) + 1;
	auto dodgePro = (*this)[attributC::dodge];
	if (dodgePro>=r)
		return true;
	return false;
}
bool ICharacter::normAtack(std::unique_ptr<ICharacter> &obj)
{
	auto damage = (*this)[attributC::damage].getValueC();
	auto armor = (*obj)[attributC::armor].getValueC();
	(*obj)[attributC::live] -= damage * (1 - armor);
	return true;
}

bool ICharacter::protect(std::unique_ptr<ICharacter>& obj)
{
	(*this)[attributC::armor].addMod(modifierT(0.5, 1));
	return true;
}

std::string ICharacter::toString()
{
	std::string str = "";
	auto allAttributes = std::vector<attributC>({ attributC::live, attributC::concentration, attributC::armor, attributC::damage, attributC::dodge });
	for (auto attr : allAttributes) {
		str += (*this)[attr].toString();
	}
	return str;
}

bool ICharacter::setSkill(int skill)
{
	if(skill>=skillsInfo.size())
		return false;
	chosenSkill = skillsInfo[skill];
	return true;
}

void ICharacter::passRound()
{
	auto attr = std::vector<attributC>({ attributC::live, attributC::concentration, attributC::armor, attributC::damage, attributC::dodge });
	for (auto at : attr)
		(*this)[at].passRound();
}
