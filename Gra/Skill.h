#pragma once
#include "pch.h"
//#include "ICharacter.h"

class Character;
using skillImpl = std::function<double()>;

class Skill
{
public:
	Skill(std::string n, bool iA, bool iM, double c, skillImpl f);
	Skill();
	~Skill();
	//get funnctions
	std::string getName();
	bool getIsAttack();
	bool getIsMySelf();
	double getCost();
	skillImpl getFn();

	// set funtion

private:

	std::string name;
	bool isAttack;
	bool isMySelf;
	double cost;
	skillImpl fn;
	//skillImpl fn;
};

