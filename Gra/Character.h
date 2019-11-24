#pragma once
#include "pch.h"
#include "IAttribute.h"
#include "ICharacter.h"
#include "Skill.h"
#include "Effect.h"

enum class attributC {live =0, concentration =1, armor=2, damage=3, dodge=4};
class Character: public ICharacter
{
public:
	Character();
	//ICharacter& operator=(const ICharacter&) = default;

	bool isDodge();
	bool isDead();// { return attributes[attributC::live].getValueC() <= 0; };

	
	std::string toString();
	bool setSkill(int skill);
	void passRound();

	//get function
	std::string getName() { return name; };
	Skill getSkill();
	//set function
private:
	double normAtack();
	double protect();
protected:

	std::string name;
	std::unordered_map<attributC, std::unique_ptr<IAttribute>> attributes;
	std::vector<Skill> skills;
	std::vector<Skill>::iterator chosenSkill;
	std::vector<Effect> effects;
	

};

