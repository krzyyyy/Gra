#pragma once
#include "pch.h"
#include "Character.h"
class Effect
{
public:
	void passRound();
	std::function<void(Character&)> getEffect();
	int detTime() { return time; };
	Effect(std::function<void(Character&)> &e);
	~Effect();
private:
	std::function<void(Character&)> effect;
	int time;
};

