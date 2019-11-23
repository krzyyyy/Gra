#include "pch.h"
#include "AttributeParam.h"


AttributeParam::AttributeParam(double dV) : defaultVal(dV), val(dV)
{

}

AttributeParam::AttributeParam() : defaultVal(0), val(0)
{
}

void AttributeParam::init()
{
	val = defaultVal;
}




void AttributeParam::modify(double a, double b)
{
	val = val * (1 + a) + b;
}

std::string AttributeParam::toString()
{
	std::string str;
	str += ": " + std::to_string(defaultVal) +"  "+ std::to_string(val)+  "\n";
	return str;
}


