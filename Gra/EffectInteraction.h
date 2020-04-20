#pragma once
#include "IInteraction.h"
#include "Character.h"
class EffectInteraction: public IInteraction
{
public:
	bool action(std::unique_ptr<ICharacter> &ofenser, std::unique_ptr<ICharacter> &target);
	EffectInteraction();
	~EffectInteraction();
};

