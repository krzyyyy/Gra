#pragma once 
#include "IInteraction.h"
class Interaction: public IInteraction
{
public:
	void action(std::unique_ptr<Character> &ofenser, std::unique_ptr<Character> &target);
	Interaction();
	~Interaction();
};

