#pragma once
#include "IField.h"
class Field: public IField
{
public:
	Field(cv::Rect r, cv::Scalar c):place(r), color(c) {};
	~Field();
	bool isClicked(cv::Point pt);
	void action();
	void draw(cv::Mat &img);

protected:
	cv::Rect place;
	cv::Scalar color;

};

