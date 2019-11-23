#pragma once
#include "pch.h"
class IField
{
public:
	virtual bool isClicked(cv::Point pt) =0;
	virtual void action() =0;
	virtual void draw(cv::InputOutputArray img)=0;
};

