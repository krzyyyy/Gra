#pragma once
#include "pch.h"
#include "ICharacter.h"
class Pomurnik: public ICharacter
{
public:
	Pomurnik();
	~Pomurnik();
	bool attack(ICharacter& obj);
	bool protect();
	
private:
	enum class skills{normAtack =0, charge = 1, metamorph = 2};
	skills skill;
	std::function<void(ICharacter&)> skillFactory();
	void charge(ICharacter& obj);
	void metamorph(ICharacter& obj);
};

