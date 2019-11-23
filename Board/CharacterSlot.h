#pragma once
#include "ICharacter.h"
#include"Field.h"
class CharacterSlot: public Field
{
public:
	CharacterSlot(cv::Rect r, cv::Scalar c): Field(r, c) {};
	bool isClicked(cv::Point pt);
	void action();
	~CharacterSlot();
private:
	
	

};

