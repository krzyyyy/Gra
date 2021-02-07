#pragma once
#include <iostream>

class IRenderObject
{
public:
	virtual void Initialize() = 0;
	virtual void Load() = 0;
	virtual ~IRenderObject() {};
};