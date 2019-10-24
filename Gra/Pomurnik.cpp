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
	if(std::get<3>(chosenSkill)<getConcentrationC())
		return false;
	return true;
}

void Pomurnik::payForAction()
{
	this->setConcentration(this->getConcentration / (1 + this->getConcentrationM()));
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
	auto damage = this->getDamageC()*2;
	auto armor = obj->getArmorC()*0.5;
	auto realDamage = damage * (1 - armor);
	obj->setLife()


}

bool Pomurnik::metamorph(std::unique_ptr<ICharacter> &obj)
{
	if (obj.get() != this)
		return false;
	setArmorM(-0.5);
	setConcentrationM(0.5);
	setDamageM(1);
	setArmorT(4);
	setConcentrationT(4);
	setDamageT(4);
	return true;
}

bool Pomurnik::normAtack(std::unique_ptr<ICharacter> &obj)
{

}

bool Pomurnik::protect(std::unique_ptr<ICharacter>& obj)
{

}



Pomurnik::Pomurnik() :ICharacter() {
	//set skills
	skillsInfo.push_back(skillInfo("normAttack", true, false, 0));
	skillsInfo.push_back(skillInfo("charge", true, false, 20));
	skillsInfo.push_back(skillInfo("metamorph", false, true, 10));
	skillsInfo.push_back(skillInfo("protect", false, true, 0));

	//set params
	this->insert({ attributC::live, Attribute(200) });
	this->insert({ attributC::concentration, Attribute(100) });
	this->insert({ attributC::armor, Attribute(0.2) });
	this->insert({ attributC::damage, Attribute(30) });
	this->insert({ attributC::dodge, Attribute(0.05) });

}