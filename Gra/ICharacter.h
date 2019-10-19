#pragma once
#include "pch.h"
#include "Attributes.h"
class ICharacter
{
public:
	virtual bool attack(ICharacter& obj) = 0;
	virtual bool protect() = 0;
	

private:
	Attributes attributes;
	virtual std::function<void(ICharacter&)> skillFactory() = 0;
	
};

