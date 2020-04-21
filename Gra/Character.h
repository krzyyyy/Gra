#pragma once
#include "IAttribute.h"
#include "ICharacter.h"
#include "IAction.h"
#include "Skill.h"
#include "Effect.h"
#include "Attack.h"
#include <unordered_map>


class EXPORT_CHARACTER Character: public ICharacter
{
public:
	Character();
	Character(const Character& obj) = delete;
	Character(Character&&)noexcept = default;
	Character& operator = (const Character& obj) = delete;
	Character& operator = (Character&& obj) = default;
	~Character() = default;
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
	double getAttribVal(attributC at);
	double getAttribDefVal(attributC at);
	//set function
	void modifAttr(attributC at, double a, double b);
	void addEffect(std::unique_ptr<IAction> eff);
private:
	std::unique_ptr<Attack> normAtack();
	std::unique_ptr<Effect> protect();
protected:

	std::string name;
	std::unordered_map<attributC, std::unique_ptr<IAttribute>> attributes;
	std::vector<Skill> skills;
	std::vector<Skill>::iterator chosenSkill;
	std::vector<std::unique_ptr<IAction>> effects;
	
};

