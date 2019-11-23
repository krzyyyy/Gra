#include "pch.h"
#include "Button.h"





Button::~Button()
{
}


void Button::draw(cv::InputOutputArray img)
{
	int baseline = 0;
	auto size = cv::getTextSize(info, cv::FONT_HERSHEY_DUPLEX, 1,1, &baseline);
	cv::putText(img, info, cv::Point(place.x+place.width/2 - (size.width/2), place.y + place.height/2 + (size.height/2)), cv::FONT_HERSHEY_DUPLEX, 1, color);
	cv::rectangle(img, place, color);
}

