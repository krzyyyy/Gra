#include "pch.h"
#include "Galadriela.h"


Galadriela::Galadriela()
{

	Skill _normAttack = Skill("Normal Attack", true, false, 0., [](ICharacter & activator, std::unique_ptr<ICharacter> &obj) {
		activator.normAtack(obj); });
	skills.push_back(_normAttack);
	Skill _glossyFinish = Skill("Gllosy Finish", true, false, 50, [](ICharacter & activator, std::unique_ptr<ICharacter> &obj) {
		Galadriela* _this = dynamic_cast<Galadriela*>(&activator);
		_this->glossyFinish(obj);
	});
	skills.push_back(_glossyFinish);
	Skill _hitOfLight = Skill("Hit Of Light", true, false, 30, [](ICharacter & activator, std::unique_ptr<ICharacter> &obj) {
		Galadriela* _this = dynamic_cast<Galadriela*>(&activator);
		_this->hitOfLight(obj);
	});
	skills.push_back(_hitOfLight);
	Skill _protect = Skill("Protect", false, true, 0., [](ICharacter & activator, std::unique_ptr<ICharacter> &obj) {
		activator.protect(obj); });
	skills.push_back(_protect);
	//skills.push_back(Skill("normAttack", true, false, 0., ));
	//skills.push_back(Skill("gllosy finish", true, false, 50., glossyFinish));
	//skills.push_back(Skill("hit of light", true, false, 0., hitOfLight));
	//skills.push_back(Skill("protect", true, false, 0., protect));
	//skillsInfo.push_back(skillInfo("normAttack", true, false, 0));
	//skillsInfo.push_back(skillInfo("gllosy finish", true, false, 50));
	//skillsInfo.push_back(skillInfo("hit of light", true, false, 30));
	//skillsInfo.push_back(skillInfo("protect", false, true, 0));

	//set params
	attributes.insert({ attributC::live, Attribute(100) });
	attributes.insert({ attributC::concentration, Attribute(200) });
	attributes.insert({ attributC::armor, Attribute(0.1) });
	attributes.insert({ attributC::damage, Attribute(40) });
	attributes.insert({ attributC::dodge, Attribute(0.1) });
}


Galadriela::~Galadriela()
{
}
bool Galadriela::action(std::unique_ptr<ICharacter> &obj) {

	if (obj->isDodge()) return false;
	auto fn = chosenSkill->getFn();
	fn(static_cast<Galadriela&>(*this), obj);
	attributes[attributC::concentration] -= chosenSkill->getCost();
	return true;
}

//std::function<void(std::unique_ptr<ICharacter>&)> Galadriela::skillFactory()
//{
//	std::function<void(std::unique_ptr<ICharacter>&)> skillPtr = nullptr; [=](std::unique_ptr<ICharacter> obj) {this->normAtack(obj); };
//	if (std::get<0>(chosenSkill) == "normAttack")
//		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->normAtack(obj); };
//	else if (std::get<0>(chosenSkill) == "gllosy finish")
//		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->glossyFinish(obj); };
//	else if (std::get<0>(chosenSkill) == "hit of light")
//		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->hitOfLight(obj); };
//	else if (std::get<0>(chosenSkill) == "protect")
//		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->protect(obj); };
//	return skillPtr;
//}

bool Galadriela::glossyFinish(std::unique_ptr<ICharacter>& obj)
{
	auto damage = 50.;
	obj->getAttribute(attributC::concentration).addMod(modifierT(-0.5, 4));
	obj->getAttribute(attributC::live) -= damage;
	return true;
}

bool Galadriela::hitOfLight(std::unique_ptr<ICharacter>& obj)
{
	auto damage = 30;
	obj->getAttribute(attributC::live) -= damage;
	return true;
}
