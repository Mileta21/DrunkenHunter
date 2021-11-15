#include "stdafx.h"
#include "RubberDuck.h"


RubberDuck::RubberDuck() : Duck()
{
	canFly = new NoFlyable();
	canQuack = new Quackable();
}

RubberDuck::RubberDuck(std::string new_name, HINSTANCE& hIn, LONG new_x, LONG new_y) : Duck(new_name, new_x, new_y)
{
	hBmp[0] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_RUBBER_BOT_LEFT));
	hBmp[1] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_RUBBER_BOT_RIGHT));
	hBmp[2] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_RUBBER_TOP_LEFT));
	hBmp[3] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_RUBBER_TOP_RIGHT));
	BITMAP bm;
	GetObject(hBmp[0], sizeof(bm), &bm);
	width = bm.bmWidth;
	height = bm.bmHeight;

	canFly = new NoFlyable();
	canQuack = new Quackable();
}

RubberDuck::RubberDuck(const RubberDuck& G) : Duck(G)
{
}


RubberDuck::~RubberDuck()
{
}

