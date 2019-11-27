#pragma once
#include "pch.h"
//#include "Character.h"
class Character;
class Effect
{
public:
	void passRound();
	// get functions 
	double getDamage();
	std::function<void( Character&)> getEffect();
	int getTime() { return time; };
	explicit Effect(std::function<void(Character&)> e, int time);
	explicit Effect(double dam);
	~Effect();
private:
	std::function<void(Character&)> effect;
	int time;
	double damage;
};

