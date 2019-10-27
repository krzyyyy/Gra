#pragma once
#include "IField.h"
class Button :
	public IField
{
public:
	Button(cv::Rect rect) :place(rect) {};
	~Button();

	bool isClicked(cv::Point pt);
	virtual void action(void * fn)=0;
	void draw(cv::InputOutputArray img, cv::Scalar color = cv::Scalar(50, 220, 60),int thicknes = 3 );
private:
	cv::Rect place;
};

