#pragma once
#include "ICharacter.h"
#include"Field.h"
class CharacterSlot: public Field
{
public:
	CharacterSlot(cv::Rect r, cv::Scalar c): Field(r, c) {};
	CharacterSlot(cv::Rect r, cv::Scalar c, std::string path);
	void draw(cv::Mat &img);
	void load(std::string path);
	void action();
	~CharacterSlot();
private:
	cv::Mat mainImage;
	

};

