#pragma once
#include "Duck.h"
class RedHeadDuck :
	public Duck
{
public:
	RedHeadDuck();
	RedHeadDuck(std::string, HINSTANCE&, LONG, LONG);
	RedHeadDuck(const RedHeadDuck&);
	virtual ~RedHeadDuck();
};

