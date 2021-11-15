#pragma once
#include "Duck.h"
class RubberDuck :
	public Duck
{
public:
	RubberDuck();
	RubberDuck(std::string, HINSTANCE&, LONG, LONG);
	RubberDuck(const RubberDuck&);
	virtual ~RubberDuck();
};

