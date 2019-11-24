#pragma once
#include "pch.h"
#include "IAttribute.h"
#include "ICharacter.h"
#include "Skill.h"
#include "Effect.h"


class Character: public ICharacter
{
public:
	Character();
	//ICharacter& operator=(const ICharacter&) = default;

	bool isDodge();
	bool isDead();// { return attributes[attributC::live].getValueC() <= 0; };

	void init();
	std::string toString();
	bool setSkill(int skill);
	void passRound();

	//get function
	std::string getName() { return name; };
	Skill getSkill();
	double getAttrib(attributC at);
	//set function
	void modifAttr(attributC at, double a, double b);
	void addEffect(Effect eff);
private:
	Effect normAtack();
	Effect protect();
protected:

	std::string name;
	std::unordered_map<attributC, std::unique_ptr<IAttribute>> attributes;
	std::vector<Skill> skills;
	std::vector<Skill>::iterator chosenSkill;
	std::vector<Effect> effects;
	

};

enum class attributC {
	live = 0,
	concentration = 1,
	armor = 2,
	damage = 3,
	dodge = 4,
	first = live,
	last = dodge
};

attributC operator++ (attributC& x) {
	return x = (attributC)(std::underlying_type<attributC>::type(x) + 1);
}
attributC operator*(attributC c) { return c; }
attributC begin(attributC r) { return attributC::first; }
attributC end(attributC r) { attributC l = attributC::last; return ++l; }