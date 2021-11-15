#include "stdafx.h"
#include "Duck.h"


Duck::Duck() : name(""), x(-1), y(-1), width(0), height(0), direction(SwimDir::NOT_MOVING), canFly(0), canQuack(0), swimToPoint(FALSE)
{
	hBmp[0] = hBmp[1] = hBmp[2] = hBmp[3] = hBmp[4] = hBmp[5] = hBmp[6] = hBmp[7] = NULL;
}

Duck::Duck(std::string new_name, LONG new_x, LONG new_y) : name(new_name),
			x(new_x), y(new_y), canFly(0), canQuack(0), width(0), height(0), direction((SwimDir)(1 + rand() % (9 - 1))), swimToPoint(FALSE)
{
	hBmp[0] = hBmp[1] = hBmp[2] = hBmp[3] = hBmp[4] = hBmp[5] = hBmp[6] = hBmp[7] = NULL;
}

Duck::Duck(const Duck& G) : name(G.name), x(G.x), y(G.y), width(G.width), height(G.height), direction(G.direction), 
			canFly(G.canFly), canQuack(G.canQuack), swimToPoint(G.swimToPoint)
{
	hBmp[0] = G.hBmp[0];
	hBmp[1] = G.hBmp[1];
	hBmp[2] = G.hBmp[2];
	hBmp[3] = G.hBmp[3];
	hBmp[4] = G.hBmp[4];
	hBmp[5] = G.hBmp[5];
	hBmp[6] = G.hBmp[6];
	hBmp[7] = G.hBmp[7];
}


Duck::~Duck()
{
}

void Duck::Swim(HRGN& hLakeRgn, POINT& pt) 
{
	if (!swimToPoint) // Если не плывем в какую-то точку, то утка плавает произвольно, ударяясь об края озера
		switch (direction) {
		case SwimDir::BOT_LEFT:
			if (!PtInRegion(hLakeRgn, x, y))
				direction = SwimDir::LEFT_TOP;
			else
			{
				x -= DUCK_MOVE_PIXELS;
				y -= DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::BOT_RIGHT:
			if (!PtInRegion(hLakeRgn, x + width, y))
				direction = SwimDir::RIGHT_TOP;
			else
			{
				x += DUCK_MOVE_PIXELS;
				y -= DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::LEFT_BOT:
			if (!PtInRegion(hLakeRgn, x + width, y + height))
				direction = SwimDir::BOT_RIGHT;
			else
			{
				x += DUCK_MOVE_PIXELS;
				y += DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::LEFT_TOP:
			if (!PtInRegion(hLakeRgn, x + width, y))
				direction = SwimDir::TOP_RIGHT;
			else
			{
				x += DUCK_MOVE_PIXELS;
				y -= DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::RIGHT_BOT:
			if (!PtInRegion(hLakeRgn, x, y + height))
				direction = SwimDir::BOT_LEFT;
			else
			{
				x -= DUCK_MOVE_PIXELS;
				y += DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::RIGHT_TOP:
			if (!PtInRegion(hLakeRgn, x, y))
				direction = SwimDir::TOP_LEFT;
			else
			{
				x -= DUCK_MOVE_PIXELS;
				y -= DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::TOP_LEFT:
			if (!PtInRegion(hLakeRgn, x, y + height))
				direction = SwimDir::LEFT_BOT;
			else
			{
				x -= DUCK_MOVE_PIXELS;
				y += DUCK_MOVE_PIXELS;
			}
			break;
		case SwimDir::TOP_RIGHT:
			if (!PtInRegion(hLakeRgn, x + width, y + height))
				direction = SwimDir::RIGHT_BOT;
			else
			{
				x += DUCK_MOVE_PIXELS;
				y += DUCK_MOVE_PIXELS;
			}
			break;
		default:
			break;
		}
	else
		SwimInPt(pt);
}

void Duck::SwimInPt(POINT& goal)
{
	if (goal.x >= x && goal.x <= x + width)
	{
		if (goal.y > y)
		{
			y += 20;
			direction = SwimDir::BOT;
		}
		else if (goal.y < y)
		{
			y -= 20;
			direction = SwimDir::TOP;
		}

	}
	else if (goal.y >= y && goal.y <= y + height)
	{
		if (goal.x > x)
		{
			x += 20;
			direction = SwimDir::RIGHT;
		}
		else if (goal.x < x)
		{
			x -= 20;
			direction = SwimDir::LEFT;
		}
	}
	else if (goal.x > x && goal.y > y)
	{
		x += 20;
		y += 20;
		direction = SwimDir::TOP_RIGHT;
	}
	else if (goal.x < x && goal.y < y)
	{
		x -= 20;
		y -= 20;
		direction = SwimDir::BOT_LEFT;
	}
	else if (goal.x > x && goal.y < y)
	{
		x += 20;
		y -= 20;
		direction = SwimDir::BOT_RIGHT;
	}
	else if (goal.x < x && goal.y > y)
	{
		x -= 20;
		y += 20;
		direction = SwimDir::TOP_LEFT;
	}
}

RECT Duck::GetRect()
{
	RECT rc;
	rc.left = x;
	rc.top = y;
	rc.right = x + width;
	rc.bottom = y + height;

	return rc;
}

void Duck::Draw(HDC& hDc, HDC& hDcm)
{
	BITMAP bm;
	switch (direction) {
	case SwimDir::BOT_LEFT: case SwimDir::RIGHT_TOP:
		GetObject(hBmp[2], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[2]);
		break;
	case SwimDir::BOT_RIGHT: case SwimDir::LEFT_TOP:
		GetObject(hBmp[3], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[3]);
		break;
	case SwimDir::TOP_LEFT: case SwimDir::RIGHT_BOT:
		GetObject(hBmp[0], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[0]);
		break;
	case SwimDir::TOP_RIGHT: case SwimDir::LEFT_BOT:
		GetObject(hBmp[1], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[1]);
		break;
	case SwimDir::TOP:
		GetObject(hBmp[4], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[4]);
		break;
	case SwimDir::BOT:
		GetObject(hBmp[5], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[5]);
		break;
	case SwimDir::RIGHT:
		GetObject(hBmp[6], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[6]);
		break;
	case SwimDir::LEFT:
		GetObject(hBmp[7], sizeof(bm), &bm);
		SelectObject(hDcm, hBmp[7]);
		break;
	default:
		break;
	}
	width = bm.bmWidth;
	height = bm.bmHeight;
	GdiTransparentBlt(hDc, x, y, width, height, hDcm, 0, 0, width, height, RGB(255, 255, 255));
}

IsFlyable * Duck::GetFlyable()
{
	return canFly;
}

RECT Duck::GetRedrawRect()
{
	RECT rc;
	rc.left = x - 20;
	rc.top = y - 20;
	rc.right = x + width + 20;
	rc.bottom = y + height + 20;

	return rc;
}

void Duck::SetSwimToPt(BOOL new_swim)
{
	swimToPoint = new_swim;
}

BOOL Duck::GetSwimToPt()
{
	return swimToPoint;
}

void Duck::SetRandDir()
{
	direction = SwimDir(1 + rand() % (9 - 1));
}

void Duck::Quack(HWND& hW, HINSTANCE& hInst)
{
	POINT pt;
	pt.x = x;
	pt.y = y - 10;
	canQuack->Quack(hW, hInst, pt);
}

void Duck::StopQuack()
{
	canQuack->StopQuack();
}
