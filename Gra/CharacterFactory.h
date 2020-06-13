#pragma once
#include <memory>
#include "Character.h"
class EXPORT_CHARACTER CharacterFactory
{
public:
	ICharacter* make_character(const std::string& name);
};

