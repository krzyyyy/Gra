#include "pch.h"
#include "Pomurnik.h"
#include "AttributeBarParam.h"
#include "AttributeParam.h"




//bool Pomurnik::action(std::unique_ptr<Character>& obj)
//{
//	obj->getAttribute(attributC::live) -= 40;
//	if (obj->isDodge()) return false;
//	auto fn = chosenSkill->getFn();
//	fn(static_cast<Pomurnik&>(*this), obj);
//	attributes[attributC::concentration] -= chosenSkill->getCost();
//	return true;
//}



Effect Pomurnik::charge()
{
	auto effFn = [this](Character & obj) {
		double attack = this->attributes[attributC::damage]->getValue() * 2;
		double armor = obj.getAttrib(attributC::armor)/2;
		double damage = (1 - armor)*attack;
		obj.modifAttr(attributC::live, 0, -damage);
	};
	Effect eff(effFn, 1);
	return eff;
}

Effect Pomurnik::metamorph()
{
	auto effFn = [](Character &obj) {
		obj.modifAttr(attributC::armor, -0.5, 0);
		obj.modifAttr(attributC::concentration, -0.5, 0);
		obj.modifAttr(attributC::damage, 1, 0);
	};
	Effect eff(effFn, 4);
	return eff;
}




Pomurnik::Pomurnik() :Character() {
	Skill _metamorph = Skill("Metamorph", false, true, 50, [this]() {
		return this->metamorph();
	});
	skills.push_back(_metamorph);
	Skill _charge = Skill("Charge", true, false, 30, [this]( ) {
		return this->charge();
	});
	skills.push_back(_charge);

	//Skill _normAttack()
	//set params
	attributes[attributC::live] = std::make_unique<AttributeBarParam>(200);
	attributes[attributC::concentration] = std::make_unique<AttributeBarParam>(100);
	attributes[attributC::armor] = std::make_unique<AttributeParam>(0.2);
	attributes[attributC::damage] = std::make_unique<AttributeParam>(30);
	attributes[attributC::dodge] = std::make_unique<AttributeParam>(0.05);


}