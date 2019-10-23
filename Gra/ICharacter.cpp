#include "pch.h"
#include "ICharacter.h"

ICharacter::ICharacter(double life_, double concentration_, double armor_, double damage_, double dodge_):
	attributes(life_, concentration_, armor_, damage_, dodge_)
{

}


bool ICharacter::isDodge()
{
	auto r = ((double)rand() / (RAND_MAX)) + 1;
	if (r >= attributes.getDodgeC())
		return true;
	return false;
}
