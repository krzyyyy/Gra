#include "pch.h"
#include "Button.h"





Button::~Button()
{
}

bool Button::isClicked(cv::Point pt)
{
	return place.contains(pt);
}


void Button::draw(cv::InputOutputArray img, cv::Scalar color , int thicknes )
{
	cv::rectangle(img, place, color);
}
