#pragma once
#include "pch.h"

#ifdef EXPORT_CHARACTER_TO_DLL
#define EXPORT_ATCTION __declspec(dllexport)
#else
#define EXPORT_ATCTION __declspec(dllimport)
#endif

class Character;
class EXPORT_ATCTION IAction
{
public:
	virtual void operator ()(Character &obj) = 0;
	virtual void passRound() = 0;
	virtual int getTime() = 0;
	virtual ~IAction() {};
};

