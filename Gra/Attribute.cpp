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
	}
	modifiers.erase(std::remove_if(modifiers.begin(), modifiers.end(), [](auto it) {
		auto[mod, time] = it;
		return time == 0;
	}), modifiers.end());
}

bool Attribute::operator>=(double v)
{
	auto final_mod = 1.;
	for (auto mod : modifiers)
		final_mod *= (1 + mod.first);
	return value >= v / final_mod;
}

std::string Attribute::toString()
{
	std::string str;
	str += ": " + std::to_string((this->getValueC())) + "\n";
	for (int i = 0; i < modifiers.size(); i++)
		str += "modifier: " + std::to_string(modifiers[i].first) + "  tours: " + std::to_string(modifiers[i].second) + "\n";
	return str;
}


