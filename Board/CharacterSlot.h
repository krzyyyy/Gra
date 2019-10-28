#pragma once
#include "ICharacter.h"
#include"IField.h"
class CharacterSlot:public IField
{
public:
	CharacterSlot(std::unique_ptr<ICharacter> &obj);
	bool isClicked(cv::Point pt);
	void action();
	void draw(cv::OutputArray img, cv::Scalar color = cv::Scalar(50, 220, 60), int thicknes = 3) = 0;
	~CharacterSlot();
private:
	std::unique_ptr<ICharacter> character;
};

