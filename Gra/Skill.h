#pragma once
#include "pch.h"
#include "IAction.h"
//#include "ICharacter.h"
//#include "Effect.h"

class Character;

class Skill
{
public:
	Skill(std::string n, bool iA, bool iM, double c, std::unique_ptr<IAction> f); 
	Skill(const Skill & skill);
	
	~Skill();
	//get funnctions
	std::string getName();
	bool getIsAttack();
	bool getIsMySelf();
	double getCost();
	std::unique_ptr<IAction> getFn();

	// set funtion

private:

	std::string name;
	bool isAttack;
	bool isMySelf;
	double cost;
	std::unique_ptr<IAction> fn;
	//skillImpl fn;
};

