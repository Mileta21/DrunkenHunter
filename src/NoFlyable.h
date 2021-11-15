#pragma once
#include "IsFlyable.h"
class NoFlyable :
	public IsFlyable
{
public:
	NoFlyable();
	virtual ~NoFlyable();
	virtual void Fly();
};

