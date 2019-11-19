#pragma once
#include "pch.h"
using  modifierT = std::pair<double, int>;
class Attribute
{
public:

	Attribute( double v) : value(v) {};
	Attribute() :value(0) {};
	/*Attribute(Attribute& atr) :value(atr.value), modifiers(atr.modifiers) {};
	Attribute(Attribute&&atr) = default;*/
	// get functions 
	
	double getValueC();
	modifierT getModifier(std::size_t idx);
	std::size_t getModifierNum() { return modifiers.size(); };
	// changing values functions
	Attribute& operator -=(double v);
	Attribute& operator +=(double v);
	//adding and deleting modifiers
	void addMod(modifierT mod) { modifiers.push_back(mod); }
	void delMod(std::size_t idx) { modifiers.erase(modifiers.begin() + idx); }
	void passRound();
	// is able
	bool operator>=(double v);
	//otrher 
	std::string toString();

private:
	double value;
	std::vector<modifierT> modifiers;
protected:
	double getValue() { return value; }
};


