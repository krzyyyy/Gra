#pragma once
#include "pch.h"
#include "Character.h"
class Pomurnik: public Character
{
public:
	Pomurnik();
	~Pomurnik() = default;
	//bool action(std::unique_ptr<Character> &obj);
	
private:
	//skillInfo chosenSkill;
	//std::function<void(std::unique_ptr<Character>&)> skillFactory();
	bool charge(std::unique_ptr<Character> &obj);
	bool metamorph(std::unique_ptr<Character> &obj);
};

