#pragma once
#include "pch.h"

class IAttribute {
public:
	virtual void init() = 0;
	virtual void modify(double a, double b)=0;
	virtual std::string toString() = 0;
	virtual double getValue() = 0;
	virtual double getDefautVal() = 0;

};