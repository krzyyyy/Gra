#pragma once
#include "pch.h"
#include "Attributes.h"
class ICharacter
{
public:
	ICharacter(double life_, double concentration_, double armor_,
		double damage_, double dodge_);
	virtual bool action(std::unique_ptr<ICharacter> &obj) = 0;
	virtual bool protect() = 0;
	//ICharacter& operator=(const ICharacter&) = default;
	

private:
	Attributes attributes;
	//virtual std::function<void(ICharacter*)> skillFactory() = 0;
	
};

