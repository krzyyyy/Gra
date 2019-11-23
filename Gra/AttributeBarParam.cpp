#include "pch.h"
#include "AttributeBarParam.h"


AttributeBarParam::AttributeBarParam()
{
}


AttributeBarParam::~AttributeBarParam()
{
}
void AttributeBarParam::modify(double a, double b)
{
	val = val * (1 + a) + b;
}