#pragma once
#include "ICharacter.h"

class IInteraction {
public:
	bool virtual action(std::unique_ptr<Character> &ofenser, std::unique_ptr<Character> &target) =0;

};