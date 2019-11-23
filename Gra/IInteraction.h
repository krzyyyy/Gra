#pragma once
#include "ICharacter.h"

class IInteraction {
public:
	void virtual action(std::unique_ptr<Character> &ofenser, std::unique_ptr<Character> &target) =0;

};