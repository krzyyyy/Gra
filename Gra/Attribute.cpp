#include "pch.h"
#include "Attribute.h"


double Attribute::getValueC()
{
	auto val = value;
	for (auto mod : modifiers)
		val *= (1 + mod.first);
	return val;
}

modifierT Attribute::getModifier(std::size_t idx)
{
	return modifiers[idx];
}

Attribute& Attribute::operator-=(double v)
{
	auto final_mod = 1.;
	for (auto mod : modifiers) 
		final_mod *= (1+mod.first);
	value -= v / final_mod;
	return *this;
}

Attribute & Attribute::operator+=(double v)
{
	auto final_mod = 1.;
	for (auto mod : modifiers)
		final_mod *= (1 + mod.first);
	value += v / final_mod;
	return *this;
}

void Attribute::passRound()
{
	for (auto it = modifiers.begin(); it != modifiers.end();it++) {
		--std::get<1>(*it);
		if (std::get<1>(*it) == 0) {
			modifiers.erase(it--);
		}
	}

}

bool Attribute::operator>=(double v)
{
	auto final_mod = 1.;
	for (auto mod : modifiers)
		final_mod *= (1 + mod.first);
	return value >= v / final_mod;
}


