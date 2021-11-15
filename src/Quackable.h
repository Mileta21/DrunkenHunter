#pragma once
#include "IsQuackable.h"
class Quackable :
	public IsQuackable
{
public:
	Quackable();
	virtual ~Quackable();
	virtual void Quack(HWND&, HINSTANCE&, POINT);
	virtual void StopQuack();
};

