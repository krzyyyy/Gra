#include "pch.h"
#include "Pomurnik.h"





bool Pomurnik::action(std::unique_ptr<ICharacter>& obj)
{
	auto skill = skillFactory();
	if (obj->isDodge()) return false;
	skill(obj);
	payForAction();
	return true;
}

bool Pomurnik::isAbleToAction()
{
	if(std::get<3>(chosenSkill)<attributes.getConcentrationC())
		return false;
	return true;
}

void Pomurnik::payForAction()
{
	this->attributes.setConcentration(this->attributes.getConcentration / (1 + this->attributes.getConcentrationM()));
}

std::function<void(std::unique_ptr<ICharacter>&)> Pomurnik::skillFactory()
{
	std::function<void(std::unique_ptr<ICharacter>&)> skillPtr = nullptr; [=](std::unique_ptr<ICharacter> obj) {this->normAtack(obj); };
	if (std::get<0>(chosenSkill)=="normAttack")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->normAtack(obj); };
	else if (std::get<0>(chosenSkill) == "charge")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->charge(obj); };
	else if (std::get<0>(chosenSkill) == "metamorph")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->metamorph(obj); };
	else if (std::get<0>(chosenSkill) == "protect")
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->protect(obj); };
	return skillPtr;
}

bool Pomurnik::charge(std::unique_ptr<ICharacter> &obj)
{
	auto damage = this->attributes.getDamageC();
	auto armor = obj->attributes.getArmorC();
}

bool Pomurnik::metamorph(std::unique_ptr<ICharacter> &obj)
{
	if (obj.get() != this || attributes.getConcentration() < 20)
		return false;
	attributes.setConcentration(attributes.getConcentrationC() - 20);
	attributes.setArmorM(-0.5);
	attributes.setConcentrationM(0.5);
	attributes.setDamageM(1);
	return true;
}

bool Pomurnik::normAtack(std::unique_ptr<ICharacter> &obj)
{

}

bool Pomurnik::protect(std::unique_ptr<ICharacter>& obj)
{

}



Pomurnik::Pomurnik():ICharacter(200, 100, 10, 20, 5) {
	skillsInfo.push_back(skillInfo("normAttack", true, false, 0));
	skillsInfo.push_back(skillInfo("charge", true, false, 20));
	skillsInfo.push_back(skillInfo("metamorph", false, true, 10));
	skillsInfo.push_back(skillInfo("protect", false, true, 0));
}