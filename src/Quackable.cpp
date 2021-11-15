#include "stdafx.h"
#include "Quackable.h"


Quackable::Quackable(): IsQuackable()
{
}


Quackable::~Quackable()
{
}

void Quackable::Quack(HWND& hW, HINSTANCE& hIn, POINT pt)
{
	hQuack = CreateWindow("static", "Кря-кря", WS_CHILD | WS_VISIBLE | SS_ELLIPSISMASK, pt.x, pt.y, 60, 20, hW, NULL, hIn, NULL);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), hIn, SND_RESOURCE | SND_ASYNC);
}

void Quackable::StopQuack()
{
	if (hQuack)
	{
		DestroyWindow(hQuack);
		hQuack = NULL;
	}
}
