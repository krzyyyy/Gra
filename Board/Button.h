#pragma once
#include "Field.h"
class Button :
	public Field
{
public:
	Button(cv::Rect r, std::string i, cv::Scalar c) :Field(r, c), info(i) {};
	void draw(cv::Mat &img);
	~Button();
	
private:
	std::string info;
	std::function<void()> run;
};

