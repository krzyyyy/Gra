#include "pch.h"
#include "Attribute.h"


modifierT Attribute::getModifier(std::size_t idx)
{
	return modifiers[idx];
}

Attribute& Attribute::operator-(double v)
{
	auto final_mod = 1.;
	for (auto mod : modifiers) 
		final_mod *= std::get<0>(mod);
	if (modifiers.empty())final_mod = 0;
	value -= v / (1 + final_mod);
	return *this;
}

Attribute & Attribute::operator+(double v)
{
	auto final_mod = 1.;
	for (auto mod : modifiers)
		final_mod *= std::get<0>(mod);
	if (modifiers.empty())final_mod = 0;
	value += v / (1 + final_mod);
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
