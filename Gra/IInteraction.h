#pragma once
#include "ICharacter.h"
#include "Character.h"

class IInteraction {
public:
	bool virtual action(std::unique_ptr<ICharacter> &ofenser, std::unique_ptr<ICharacter> &target) =0;

};