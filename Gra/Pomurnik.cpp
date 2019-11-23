#include "pch.h"
#include "Pomurnik.h"





//bool Pomurnik::action(std::unique_ptr<Character>& obj)
//{
//	obj->getAttribute(attributC::live) -= 40;
//	if (obj->isDodge()) return false;
//	auto fn = chosenSkill->getFn();
//	fn(static_cast<Pomurnik&>(*this), obj);
//	attributes[attributC::concentration] -= chosenSkill->getCost();
//	return true;
//}



double Pomurnik::charge()
{
	auto damage = attributes[attributC::damage].getValueC()*2;
	return damage;
}

double Pomurnik::metamorph()
{
	attributes[attributC::armor].addMod(modifierT(-0.5, 4));
	attributes[attributC::concentration].addMod(modifierT(-0.5, 4));
	attributes[attributC::damage].addMod(modifierT(1, 4));
	return 0.;
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
	attributes.insert({ attributC::live, Attribute(200) });
	attributes.insert({ attributC::concentration, Attribute(100) });
	attributes.insert({ attributC::armor, Attribute(0.2) });
	attributes.insert({ attributC::damage, Attribute(30) });
	attributes.insert({ attributC::dodge, Attribute(0.05) });

}