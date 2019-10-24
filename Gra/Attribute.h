#pragma once
using  modifierT = std::pair<double, int>;
class Attribute
{
public:

	Attribute(std::string n, double v) :name(n), value(v) {};
	
	// get functions 
	double getValue() { return value; }
	std::string getName() { return name; }
	modifierT getModifier(std::size_t idx);
	// changing values functions
	Attribute& operator -(double v);
	Attribute& operator +(double v);
	//adding and deleting modifiers
	void addMod(modifierT mod) { modifiers.push_back(mod); }
	void delMod(std::size_t idx) { modifiers.erase(modifiers.begin() + idx); }
	void passRound();

private:
	const std::string name;
	double value;
	std::vector<modifierT> modifiers;
};


