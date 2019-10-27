#include "pch.h"
#include "Galadriela.h"


Galadriela::Galadriela()
{
	skillsInfo.push_back(skillInfo("normAttack", true, false, 0));
	skillsInfo.push_back(skillInfo("gllosy finish", true, false, 50));
	skillsInfo.push_back(skillInfo("hit of light", true, false, 30));
	skillsInfo.push_back(skillInfo("protect", false, true, 0));

	//set params
	this->insert({ attributC::live, Attribute(100) });
	this->insert({ attributC::concentration, Attribute(200) });
	this->insert({ attributC::armor, Attribute(0.1) });
	this->insert({ attributC::damage, Attribute(40) });
	this->insert({ attributC::dodge, Attribute(0.1) });
}


Galadriela::~Galadriela()
{
}
bool Galadriela::action(std::unique_ptr<ICharacter> &obj) {

	auto skill = skillFactory();
	if (obj->isDodge()) return false;
	skill(obj);
	(*this)[attributC::concentration] -= std::get<3>(chosenSkill);
	return true;
}

std::function<void(std::unique_ptr<ICharacter>&)> Galadriela::skillFactory()
{
	std::function<void(std::unique_ptr<ICharacter>&)> skillPtr = nullptr; [=](std::unique_ptr<ICharacter> obj) {this->normAtack(obj); };
	if (std::get<0>(chosenSkill) == "normAttack")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->normAtack(obj); };
	else if (std::get<0>(chosenSkill) == "gllosy finish")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->glossyFinish(obj); };
	else if (std::get<0>(chosenSkill) == "hit of light")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->hitOfLight(obj); };
	else if (std::get<0>(chosenSkill) == "protect")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->protect(obj); };
	return skillPtr;
}

bool Galadriela::glossyFinish(std::unique_ptr<ICharacter>& obj)
{
	auto damage = 50.;
	(*obj)[attributC::concentration].addMod(modifierT(-0.5, 4));
	(*obj)[attributC::live] -= damage;
	return true;
}

bool Galadriela::hitOfLight(std::unique_ptr<ICharacter>& obj)
{
	auto damage = 30;
	(*obj)[attributC::live] -= damage;
	return true;
}
