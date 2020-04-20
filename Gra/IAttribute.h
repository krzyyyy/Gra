#pragma once
#include "pch.h"

#ifdef EXPORT_CHARACTER_TO_DLL
#define EXPORT_ATTRIBUTE __declspec(dllexport)
#else
#define EXPORT_ATTRIBUTE __declspec(dllimport)
#endif

class EXPORT_ATTRIBUTE IAttribute {
public:
	virtual void init() = 0;
	virtual void modify(double a, double b)=0;
	virtual std::string toString() = 0;
	virtual double getValue() = 0;
	virtual double getDefautVal() = 0;

};