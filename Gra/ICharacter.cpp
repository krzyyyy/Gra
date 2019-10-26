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
	(*obj)[attributC::armor] -= damage * (1 - armor);
}

bool ICharacter::protect(std::unique_ptr<ICharacter>& obj)
{

}