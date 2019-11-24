#include "pch.h"
#include "AttributeBarParam.h"


AttributeBarParam::AttributeBarParam()
{
}


AttributeBarParam::~AttributeBarParam()
{
}
void AttributeBarParam::init()
{

}
void AttributeBarParam::modify(double a, double b)
{
	val = val * (1 + a) + b;
}

std::string AttributeBarParam::toString()
{
	std::string str;
	str += ": " + std::to_string(defaultVal) + "  " + std::to_string(val) + "\n";
	return str;
}
