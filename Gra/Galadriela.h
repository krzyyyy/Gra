#pragma once
#include "ICharacter.h"
class Galadriela: public ICharacter
{
public:
	Galadriela();
	~Galadriela();
	bool action(std::unique_ptr<ICharacter> &obj);
private:
	
	std::function<void(std::unique_ptr<ICharacter>&)> skillFactory();
	bool glossyFinish(std::unique_ptr<ICharacter>& obj);
	bool hitOfLight(std::unique_ptr<ICharacter>& obj);

};

