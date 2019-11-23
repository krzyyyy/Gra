#include "pch.h"
#include "CharacterSlot.h"





CharacterSlot::CharacterSlot(cv::Rect r, cv::Scalar c, std::string path): Field(r, c)
{
	load(path);
}

void CharacterSlot::draw(cv::Mat &img)
{
	mainImage.copyTo(img(place));
}

void CharacterSlot::load(std::string path)
{
	mainImage = cv::imread(path + "/main.jpg");
	cv::resize(mainImage, mainImage,place.size(), 0, 0);
}


void CharacterSlot::action()
{
}


CharacterSlot::~CharacterSlot()
{
}
