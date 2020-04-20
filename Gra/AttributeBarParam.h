#pragma once
#include "IAttribute.h"

class EXPORT_ATTRIBUTE AttributeBarParam: public IAttribute
{
public:

	AttributeBarParam(double v);
	~AttributeBarParam();

	void init();
	/*Attribute(Attribute& atr) :value(atr.value), modifiers(atr.modifiers) {};
	Attribute(Attribute&&atr) = default;*/
	// get functions 
	void modify(double a, double b);
	//otrher 
	std::string toString();
	double getValue() { return val; }
	double getDefautVal() { return defaultVal; };
private:
	double val;
	double defaultVal;
};

