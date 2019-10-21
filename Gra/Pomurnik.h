#pragma once
#include "pch.h"
#include "ICharacter.h"
class Pomurnik: public ICharacter
{
public:
	Pomurnik();
	~Pomurnik() = default;
	bool action(std::unique_ptr<ICharacter> &obj);
	//bool protect();
	
private:
	enum class skills{normAtack =0, protect =1, charge = 2, metamorph = 3};
	skills skill;
	std::function<void(std::unique_ptr<ICharacter>&)> skillFactory();
	void charge(std::unique_ptr<ICharacter> &obj);
	void metamorph(std::unique_ptr<ICharacter> &obj);
	void normAtack(std::unique_ptr<ICharacter> &obj);
	void protect(std::unique_ptr<ICharacter> &obj);
};

