#include "stdafx.h"
#include "Hunter.h"


Hunter::Hunter() : name(""), onTheHunt(false), hBmp(NULL), width(0), height(0)
{
}

Hunter::Hunter(std::string new_name, bool attend, HINSTANCE& hIn) : name(new_name), onTheHunt(attend)
{
	hBmp = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_HUNTER));
	BITMAP bm;
	GetObject(hBmp, sizeof(bm), &bm);
	width = bm.bmWidth;
	height = bm.bmHeight;
}

Hunter::Hunter(const Hunter& G) : name(G.name), onTheHunt(G.onTheHunt), hBmp(G.hBmp), width(G.width), height(G.height){}


Hunter::~Hunter()
{
}

void Hunter::AttendLake()
{
	onTheHunt = true;
}

void Hunter::LeaveLake()
{
	onTheHunt = false;
}

bool Hunter::IsHunterAtLake()
{
	return onTheHunt;
}

void Hunter::SetBitmap(HINSTANCE& hIn)
{
	hBmp = LoadBitmap(hIn, MAKEINTRESOURCE(IDB_HUNTER));
	BITMAP bm;
	GetObject(hBmp, sizeof(bm), &bm);
	width = bm.bmWidth;
	height = bm.bmHeight;
}

RECT Hunter::GetRect()
{
	RECT rc;
	rc.left = 20 - 15;
	rc.top = 20 - 15;
	rc.right = 20 + width + 15;
	rc.bottom = 20 + height + 15;

	return rc;
}

void Hunter::DrawHunter(HDC& hDc)
{
	HDC hDcm = CreateCompatibleDC(hDc);
	SelectObject(hDcm, hBmp);
	GdiTransparentBlt(hDc, 20, 20, width, height, hDcm, 0, 0, width, height, RGB(255, 255, 255));
	DeleteDC(hDcm);
}
