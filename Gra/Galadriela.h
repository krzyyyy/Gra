#pragma once
#include "Character.h"
class Galadriela: public Character
{
public:
	Galadriela();
	~Galadriela();
	//bool action(std::unique_ptr<Character> &obj);
private:
	
	//std::function<void(std::unique_ptr<ICharacter>&)> skillFactory();
	bool glossyFinish(std::unique_ptr<Character>& obj);
	bool hitOfLight(std::unique_ptr<Character>& obj);

};

