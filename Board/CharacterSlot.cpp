#include "pch.h"
#include "CharacterSlot.h"




CharacterSlot::CharacterSlot(std::unique_ptr<ICharacter>& obj, cv::Mat & img)
{

}

bool CharacterSlot::isClicked(cv::Point pt)
{
	return false;
}

void CharacterSlot::action()
{
}

CharacterSlot::~CharacterSlot()
{
}
