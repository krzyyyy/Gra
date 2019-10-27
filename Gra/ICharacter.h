#pragma once
#include "pch.h"
#include "Attribute.h"
#include <unordered_map>
enum class attributC {live =0, concentration =1, armor=2, damage=3, dodge=4};
class ICharacter: public std::unordered_map<attributC, Attribute>
{
public:
	virtual bool action(std::unique_ptr<ICharacter> &obj) = 0;
	//ICharacter& operator=(const ICharacter&) = default;

	bool isDodge();
	bool isDead() { return (*this)[attributC::live].getValueC() <= 0; };
	bool normAtack(std::unique_ptr<ICharacter> &obj);
	bool protect(std::unique_ptr<ICharacter> &obj);
	
	std::string toString();
	bool setSkill(int skill);
	void passRound();
private:
protected:
	using skillInfo = std::tuple<std::string, bool, bool, double>;//< name, is attack action, is myself acction, cost of concentration>
	std::vector<skillInfo > skillsInfo;
	skillInfo chosenSkill;
	
	//virtual std::function<void(ICharacter*)> skillFactory() = 0;
	
};

