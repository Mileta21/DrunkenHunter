#pragma once
#include "IsFlyable.h"
class Flyable :
	public IsFlyable
{
public:
	Flyable();
	virtual ~Flyable();
	virtual void Fly();
};

