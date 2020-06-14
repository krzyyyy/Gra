#pragma once
#include <memory>
#include "ICharacter.h"
#include <msclr/marshal.h>
#include <msclr\marshal_cppstd.h>
using namespace System;

namespace ModelWrapper {
	public ref class WCharacter
	{
	public:
		WCharacter();
		WCharacter(System::String^ name);
		~WCharacter();
		System::Boolean isDead();
		System::Void setSkill(System::Int32 skill);
		System::Void passRound();
		// TODO: Add your methods for this class here.
	private:
		ICharacter* character;
	};
}
