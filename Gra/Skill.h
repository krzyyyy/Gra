#pragma once
#include "pch.h"
#include "IAction.h"
//#include "ICharacter.h"
//#include "Effect.h"
using ImplEff = std::function<std::unique_ptr<IAction>()>;
class Character;

class Skill
{
public:
	Skill(std::string n, bool iA, bool iM, double c, ImplEff f);
	Skill(const Skill & skill);
	Skill();
	~Skill();
	//get funnctions
	std::string getName();
	bool getIsAttack();
	bool getIsMySelf();
	double getCost();
	ImplEff getFn();

	// set funtion

private:

	std::string name;
	bool isAttack;
	bool isMySelf;
	double cost;
	ImplEff fn;
	//skillImpl fn;
};

