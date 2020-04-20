﻿// Gra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Pomurnik.h"
#include "Galadriela.h"
#include "ICharacter.h"
#include "EffectInteraction.h"

int main()
{
	int tourConter = 0;
	EffectInteraction interaction;
	std::vector<std::string> names({ "pomurnik",  "galadiera" });
	std::vector<std::unique_ptr<ICharacter>> characters;
	characters.emplace_back(std::make_unique<Pomurnik>());
	characters.emplace_back(std::make_unique<Galadriela>());
	int player = 0;
	int skill = 0;
	while (!characters[player%2]->isDead() && !characters[(player+1) % 2]->isDead()) {
		std::cout << "Podaj numer skilla:  ";
		std::cin >> skill;
		if (characters[player % 2]->setSkill(skill))
			interaction.action(characters[player % 2], characters[(player + 1) % 2]);
		else
			continue;
		std::cout <<"Aggresor: "+names[player % 2 ]+"\n"<< characters[player % 2]->toString();
		std::cout <<"Defender: "+names[(player + 1) % 2] +"\n"<< characters[(player+1) % 2]->toString();
		std::cout << player++ << std::endl;
		
		characters[(player + 1) % 2]->passRound();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
