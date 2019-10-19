#pragma once
#include "pch.h"
class ICharacter
{
public:
	virtual ~ICharacter() =0;
	virtual bool attack(ICharacter& obj) = 0;
	virtual bool protect() = 0;
	virtual std::function<void(ICharacter&)> skillFactory() =0;

	double getLife() { return life; }
	double getConcentration() { return concentration; }
	double getDefens() { return defense; }
	double getDamage() { return damage; }
	// sets group
	void setLife(double l) { life = l; }
	void setConcentration(double c) { concentration = c; }
	void setDefense(double d) { defense = d; }
	void setDamage(double d) { damage = d; }

private:
	double life;
	double concentration;
	double defense;
	double damage;
	
};

