#pragma once
class IField
{
public:

	virtual bool isClicked(cv::Point pt) =0;
	virtual void action() =0;
	virtual void draw(cv::OutputArray img, cv::Scalar color = cv::Scalar(50, 220, 60), int thicknes = 3)=0;
	std::string getName() { return name; };
	void setName(std::string n) { name = n; };
private:
	std::string name;
};

