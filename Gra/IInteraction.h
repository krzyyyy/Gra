#pragma once
#include "ICharacter.h"

class IInteraction {
public:
	bool virtual action(std::unique_ptr<ICharacter> &ofenser, std::unique_ptr<ICharacter> &target) =0;

};