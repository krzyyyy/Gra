#pragma once
#include "Character.h"
class EXPORT_CHARACTER Galadriela: public Character
{
public:
	Galadriela();
	~Galadriela();
private:
	std::unique_ptr<Effect> glossyFinish();
	std::unique_ptr<Attack> hitOfLight();

};

