#pragma once
#include "pch.h"

class IAttribute {
public:
	virtual void init() = 0;
	virtual void modify(double a, double b);

};