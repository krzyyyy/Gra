#pragma once
#include "IAttribute.h"
class EXPORT_ATTRIBUTE AttributeParam: public IAttribute
{
public:

	AttributeParam( double dV) ;
	AttributeParam();
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
	const double defaultVal;	
};


