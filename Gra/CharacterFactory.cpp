#include "pch.h"
#include "CharacterFactory.h"
#include "Pomurnik.h"
#include "Galadriela.h"

ICharacter* CharacterFactory::make_character(const std::string& name)
{
	if (name == "Pomurnik")
		return new Pomurnik();
	else if (name == "Galadriela")
		return new Galadriela();
	return nullptr;
}
