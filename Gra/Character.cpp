#include "pch.h"
#include "Character.h"
using namespace std;

attributC operator++ (attributC& x) {
	return x = (attributC)(std::underlying_type<attributC>::type(x) + 1);
}
attributC operator*(attributC c) { return c; }
attributC begin(attributC r) { return attributC::first; }
attributC end(attributC r) { attributC l = attributC::last; return ++l; }


Character::Character()
{
	Skill _normAttack = Skill("Normal Attack", true, false, 0., this->normAtack());
	skills.push_back(_normAttack);
	Skill _protect = Skill("Protect", false, true, 0., this->protect());
	skills.push_back(_protect);
}


bool Character::isDodge()
{
	auto r = ((double)rand() / (RAND_MAX)) + 1;
	auto dodgePro = attributes[attributC::dodge]->getValue();
	if (dodgePro>=r)
		return true;
	return false;
}
bool Character::isDead()
{
	double live = attributes[attributC::live]->getValue();
	return  live <=0.;
}
std::unique_ptr<Attack> Character::normAtack()
{	
	//unique_ptr<IAction> ptr = // new Attack(2 * attributes[attributC::damage]->getValue());
	return make_unique<Attack>(2 * attributes[attributC::damage]->getValue());
}

std::unique_ptr<Effect> Character::protect()
{
	auto eff = [](Character & obj) {
		obj.modifAttr(attributC::armor, 0.5, 0);
	};
	
	return make_unique<Effect>(eff, 1);

}

void Character::init()
{
	for (auto at : attributC()) {
		attributes[at]->init();
	}
	for (auto &effect : effects) {
		
		effect->operator()(*this);
	}

}

std::string Character::toString()
{
	std::string str = "";
	for (auto att : attributC()) {
		str += typeid(att).name()+ attributes[att]->toString();
	}
	return str;
}

bool Character::setSkill(int skill)
{
	if(skill>=skills.size())
		return false;
	chosenSkill = skills.begin()+skill;
	return true;
}

void Character::passRound()
{
	for (auto &effect : effects) {
		effect->passRound();
	}
	effects.erase(std::remove_if(effects.begin(), effects.end(), [](auto elem) {
		return elem->getTime() == 0;
	}));
}

Skill Character::getSkill()
{
	return *chosenSkill;
}

double Character::getAttrib(attributC at)
{

	return attributes[at]->getValue();
}

void Character::modifAttr(attributC at, double a, double b)
{
	attributes[at]->modify(a, b);
}

void Character::addEffect(std::unique_ptr<IAction> eff)
{
	eff->operator()(*this);
	effects.emplace_back(move(eff));
}

