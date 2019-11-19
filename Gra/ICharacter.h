#pragma once
#include "pch.h"
#include "Attribute.h"
#include <unordered_map>
#include "Skill.h"

enum class attributC {live =0, concentration =1, armor=2, damage=3, dodge=4};
class ICharacter
{
public:
	virtual bool action(std::unique_ptr<ICharacter> &obj) = 0;
	//ICharacter& operator=(const ICharacter&) = default;

	bool isDodge();
	bool isDead() { return attributes[attributC::live].getValueC() <= 0; };
	void normAtack(std::unique_ptr<ICharacter> &obj);
	bool protect(std::unique_ptr<ICharacter> &obj);
	
	std::string toString();
	bool setSkill(int skill);
	void passRound();

	//get function
	std::string getName() { return name; };
	Attribute getAttribute(attributC at) { return attributes[at]; };
	//set function
private:
	
protected:

	std::string name;
	std::unordered_map<attributC, Attribute> attributes;
	std::vector<Skill> skills;
	std::vector<Skill>::iterator chosenSkill;
	
};

