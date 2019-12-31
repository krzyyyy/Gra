#pragma once
#include "IAction.h"
class Attack: public IAction
{
public:
	Attack(double a);
	void operator ()(Character &obj);
	void passRound();
	int getTime();
	~Attack();
private:
	double attack;
};

