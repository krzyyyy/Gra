#pragma once
#include "pch.h"
#include "IAction.h"
class EXPORT_ATCTION Effect: public IAction
{
public:
	Effect();
	void passRound();
	// get functions 
	std::function<void( Character&)> getEffectFn();
	int getTime() { return time; };
	explicit Effect(std::function<void(Character&)> e, int time);
	void operator ()(Character & obj);
	~Effect();
private:
	std::function<void(Character&)> effect;
	int time;
};

