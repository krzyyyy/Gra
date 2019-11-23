#include "pch.h"
#include "Field.h"





Field::~Field()
{
}

bool Field::isClicked(cv::Point pt)
{
	return place.contains(pt);
}

void Field::action()
{

}

void Field::draw(cv::InputOutputArray img)
{
	cv::rectangle(img, place, color);
}
