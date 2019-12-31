#pragma once
#include "pch.h"
class Character;
class ICharacter
{
public:
	virtual void init() = 0;
	virtual void passRound() = 0;


};