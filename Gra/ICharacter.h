#pragma once
#include "pch.h"
class Character;
class ICharacter
{
public:
	virtual bool action(std::unique_ptr<Character> &obj)=0;

};