#pragma once
#include "pch.h"
class Skill;
class IAction;

#ifdef EXPORT_CHARACTER_TO_DLL
#define EXPORT_CHARACTER __declspec(dllexport)
#else
#define EXPORT_CHARACTER __declspec(dllimport)
#endif
enum class EXPORT_CHARACTER attributC {
	live = 0,
	concentration = 1,
	armor = 2,
	damage = 3,
	dodge = 4,
	first = live,
	last = dodge

};

class EXPORT_CHARACTER ICharacter
{
public:
	virtual bool isDodge() =0;
	virtual bool isDead() =0;// { return attributes[attributC::live].getValueC() <= 0; };

	virtual void init() = 0;
	virtual std::string toString() =0 ;
	virtual bool setSkill(int skill) = 0;
	virtual void passRound() = 0;

	//get function
	virtual std::string getName()  = 0;
	virtual Skill getSkill() = 0;
	virtual double getAttrib(attributC at) = 0;
	//set function
	virtual void modifAttr(attributC at, double a, double b) = 0;
	virtual void addEffect(std::unique_ptr<IAction> eff) = 0;
	virtual ~ICharacter() {};


};