#include "pch.h"
#include "Pomurnik.h"




bool Pomurnik::action(std::unique_ptr<ICharacter>& obj)
{
	auto skill = skillFactory();
	if (skill == nullptr)return false;
	skill(obj);
	return true;
}

std::function<void(std::unique_ptr<ICharacter>&)> Pomurnik::skillFactory()
{
	std::function<void(std::unique_ptr<ICharacter>&)> skillPtr = nullptr; [=](std::unique_ptr<ICharacter> obj) {this->normAtack(obj); };
	if (skill == skills::normAtack)
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->normAtack(obj); };
	else if (skill == skills::charge)
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->charge(obj); };
	else if (skill == skills::metamorph)
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->metamorph(obj); };
	else if (skill == skills::protect)
		skillPtr = [=](std::unique_ptr<ICharacter> &obj) {this->protect(obj); };
	return skillPtr;
}

void Pomurnik::charge(std::unique_ptr<ICharacter> &obj)
{

}

void Pomurnik::metamorph(std::unique_ptr<ICharacter> &obj)
{
}

void Pomurnik::normAtack(std::unique_ptr<ICharacter> &obj)
{

}

void Pomurnik::protect(std::unique_ptr<ICharacter>& obj)
{

}



Pomurnik::Pomurnik():ICharacter(200, 100, 10, 20, 5) {

}