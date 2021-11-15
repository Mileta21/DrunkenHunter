#include "stdafx.h"
#include "RedHeadDuck.h"


RedHeadDuck::RedHeadDuck() : Duck()
{
	canFly = new Flyable();
	canQuack = new Quackable();
}

RedHeadDuck::RedHeadDuck(std::string new_name, HINSTANCE& hIn, LONG new_x, LONG new_y) : Duck(new_name, new_x, new_y)
{
	hBmp[0] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_BOT_LEFT));
	hBmp[1] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_BOT_RIGHT));
	hBmp[2] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_TOP_LEFT));
	hBmp[3] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_TOP_RIGHT));
	hBmp[4] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_TOP));
	hBmp[5] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_BOT));
	hBmp[6] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_RIGHT));
	hBmp[7] = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_REDHEAD_LEFT));
	BITMAP bm;
	GetObject(hBmp[0], sizeof(bm), &bm);
	width = bm.bmWidth;
	height = bm.bmHeight;

	canFly = new Flyable();
	canQuack = new Quackable();
}

RedHeadDuck::RedHeadDuck(const RedHeadDuck& G) : Duck(G)
{
}


RedHeadDuck::~RedHeadDuck()
{
}

