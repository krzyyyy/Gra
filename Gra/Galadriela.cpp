#include "pch.h"
#include "Galadriela.h"


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
	attributes.insert({ attributC::live, Attribute(100) });
	attributes.insert({ attributC::concentration, Attribute(200) });
	attributes.insert({ attributC::armor, Attribute(0.1) });
	attributes.insert({ attributC::damage, Attribute(40) });
	attributes.insert({ attributC::dodge, Attribute(0.1) });
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


double Galadriela::glossyFinish()
{
	//auto damage = 50.;
	//obj->setAttributeMod(attributC::concentration, modifierT(-0.5, 4));
	//obj->hurt( damage);
	return 50.;
}

double Galadriela::hitOfLight()
{
	//auto damage = 30;
	//obj->hurt( damage);
	return 30.;
}
