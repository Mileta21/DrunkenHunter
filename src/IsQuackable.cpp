#include "stdafx.h"
#include "IsQuackable.h"


IsQuackable::IsQuackable() : hQuack(NULL)
{
}


IsQuackable::~IsQuackable()
{
	if (hQuack)
		DestroyWindow(hQuack);
}
