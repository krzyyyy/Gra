#pragma once
#include "pch.h"
#include "ICharacter.h"
class Pomurnik: public ICharacter
{
public:
	Pomurnik();
	~Pomurnik() = default;
	bool action(std::unique_ptr<ICharacter> &obj);
	bool isAbleToAction();
	void payForAction();
	
private:
	skillInfo chosenSkill;
	std::function<void(std::unique_ptr<ICharacter>&)> skillFactory();
	bool charge(std::unique_ptr<ICharacter> &obj);
	bool metamorph(std::unique_ptr<ICharacter> &obj);
	bool normAtack(std::unique_ptr<ICharacter> &obj);
	bool protect(std::unique_ptr<ICharacter> &obj);
};

