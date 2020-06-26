#pragma once
//#include <memory>
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
		bool^ isDead();
		void setSkill(System::Int32 skill);
		void passRound();
		 //TODO: Add your methods for this class here.
	private:
		ICharacter* character;
	};
}
