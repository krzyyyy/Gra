#pragma once
#include "IField.h"
class Field: public IField
{
public:
	Field(cv::Rect r, cv::Scalar c):place(r), color(c) {};
	~Field();
	bool isClicked(cv::Point pt);
	void action();
	void draw(cv::InputOutputArray img);

protected:
	cv::Rect place;
	cv::Scalar color;

};

