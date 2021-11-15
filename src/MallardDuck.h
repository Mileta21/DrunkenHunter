#pragma once
#include "Duck.h"
class MallardDuck :
	public Duck
{
public:
	MallardDuck();
	MallardDuck(std::string, HINSTANCE&, LONG, LONG);
	MallardDuck(const MallardDuck&);
	virtual ~MallardDuck();
};

