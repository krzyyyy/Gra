#include "pch.h"
#include "Pomurnik.h"





bool Pomurnik::action(std::unique_ptr<ICharacter>& obj)
{
	auto skill = skillFactory();
	if (obj->isDodge()) return false;
	skill(obj);
	//(*this)[attributC::concentration] -= std::get<3>(chosenSkill);
	return true;
}


std::function<void(std::unique_ptr<ICharacter>&)> Pomurnik::skillFactory()
{
	//std::function<void(std::unique_ptr<ICharacter>&)> skillPtr = nullptr; [=](std::unique_ptr<ICharacter> obj) {this->normAtack(obj); };
	//if (std::get<0>(chosenSkill)=="normAttack")
	//	skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->normAtack(obj); };
	//else if (std::get<0>(chosenSkill) == "charge")
	//	skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->charge(obj); };
	//else if (std::get<0>(chosenSkill) == "metamorph")
	//	skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->metamorph(obj); };
	//else if (std::get<0>(chosenSkill) == "protect")
	//	skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->protect(obj); };
	return nullptr;
}

bool Pomurnik::charge(std::unique_ptr<ICharacter> &obj)
{
	auto damage = attributes[attributC::damage].getValueC()*2;
	auto armor = obj->getAttribute(attributC::armor).getValueC()*0.5;
	auto realDamage = damage * (1 - armor);
	obj->getAttribute(attributC::live) -= realDamage;
	return true;
}

bool Pomurnik::metamorph(std::unique_ptr<ICharacter> &obj)
{
	attributes[attributC::armor].addMod(modifierT(-0.5, 4));
	attributes[attributC::concentration].addMod(modifierT(-0.5, 4));
	attributes[attributC::damage].addMod(modifierT(1, 4));
	return true;
}




Pomurnik::Pomurnik() :ICharacter() {
	//set skills
	//skillsInfo.push_back(skillInfo("normAttack", true, false, 0));
	//skillsInfo.push_back(skillInfo("charge", true, false, 20));
	//skillsInfo.push_back(skillInfo("metamorph", false, true, 10));
	//skillsInfo.push_back(skillInfo("protect", false, true, 0));

	//set params
	attributes.insert({ attributC::live, Attribute(200) });
	attributes.insert({ attributC::concentration, Attribute(100) });
	attributes.insert({ attributC::armor, Attribute(0.2) });
	attributes.insert({ attributC::damage, Attribute(30) });
	attributes.insert({ attributC::dodge, Attribute(0.05) });

}