#include "pch.h"
#include "Galadriela.h"
#include "AttributeBarParam.h"
#include "AttributeParam.h"


Galadriela::Galadriela()
{

	Skill _glossyFinish = Skill("Gllosy Finish", true, false, 50, [this]() {
		return this->glossyFinish();
	});
	skills.push_back(_glossyFinish);
	Skill _hitOfLight = Skill("Hit Of Light", true, false, 30, [this]( ) {
		return this->hitOfLight();
	});
	skills.push_back(_hitOfLight);

	//set params

	attributes[attributC::live] = std::make_unique<AttributeBarParam>(100);
	attributes[attributC::concentration] = std::make_unique<AttributeBarParam>(200);
	attributes[attributC::armor] = std::make_unique<AttributeParam>(0.1);
	attributes[attributC::damage] = std::make_unique<AttributeParam>(40);
	attributes[attributC::dodge] = std::make_unique<AttributeParam>(0.1);
}


Galadriela::~Galadriela()
{
}
//bool Galadriela::action(std::unique_ptr<Character> &obj) {
//
//	if (obj->isDodge()) return false;
//	auto fn = chosenSkill->getFn();
//	fn(static_cast<Galadriela&>(*this), obj);
//	attributes[attributC::concentration] -= chosenSkill->getCost();
//	return true;
//}


Effect Galadriela::glossyFinish()
{
	auto effFn = [](Character & obj) {
		obj.modifAttr(attributC::concentration, -0.5, 4);
		obj.modifAttr(attributC::live, 0, -50);
	};
	Effect eff(effFn, 1);
	return eff;
}

Effect Galadriela::hitOfLight()
{
	double damage  =30.;
	return Effect(damage);
}
