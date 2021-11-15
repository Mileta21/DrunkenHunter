#pragma once
#include "IsQuackable.h"
class NoQuackable :
	public IsQuackable
{
public:
	NoQuackable();
	virtual ~NoQuackable();
	virtual void Quack(HWND&, HINSTANCE&, POINT);
	virtual void StopQuack();
};

