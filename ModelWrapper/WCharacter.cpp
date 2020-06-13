#include "pch.h"
#include "WCharacter.h"
#include "CharacterFactory.h"
#include <memory>
#include <msclr\marshal_cppstd.h>

ModelWrapper::WCharacter::WCharacter(System::String^ name)
{
	std::string cpp_name = msclr::interop::marshal_as<std::string>(name);
	auto factory = CharacterFactory();
	character = factory.make_character(cpp_name);
}
ModelWrapper::WCharacter::~WCharacter()
{
	if (character != nullptr)
		delete character;
	
}
System::Boolean ModelWrapper::WCharacter::isDead()
{
	return character->isDead();
}

System::Void ModelWrapper::WCharacter::setSkill(System::Int32 skill)
{
	character->setSkill(skill);
	return System::Void();
}

System::Void ModelWrapper::WCharacter::passRound()
{
	character->passRound();
	return System::Void();
}
