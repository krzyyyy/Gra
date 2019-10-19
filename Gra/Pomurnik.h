#pragma once
#include "pch.h"
#include "ICharacter.h"
#include "ISkill.h"
class Pomurnik: public ICharacter
{
public:
	Pomurnik();
	bool attack(ICharacter& obj);
	bool protect();
	std::function<void(ICharacter&)> skillFactory();
private:
	enum class skills{normAtack =0, charge = 1, metamorph = 2};
	skills skill;
	~Pomurnik();
};

