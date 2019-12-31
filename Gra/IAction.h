#pragma once

class Character;
class IAction
{
public:
	virtual void operator ()(Character &obj) = 0;
	virtual void passRound() = 0;
	virtual int getTime() = 0;
	virtual ~IAction() =0;
};

