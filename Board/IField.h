#pragma once
#include "pch.h"
class IField
{
public:
	virtual bool isClicked(cv::Point pt) =0;
	virtual void action() =0;
	virtual void draw(cv::Mat &img)=0;
};

