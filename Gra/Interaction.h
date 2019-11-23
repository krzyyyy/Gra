#pragma once 
#include "IInteraction.h"
#include "Character.h"
class Interaction: public IInteraction
{
public:
	bool action(std::unique_ptr<Character> &ofenser, std::unique_ptr<Character> &target);
	Interaction();
	~Interaction();
};

