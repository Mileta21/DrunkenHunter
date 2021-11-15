#pragma once
#include "IsFlyable.h"
#include "IsQuackable.h"
typedef enum {NOT_MOVING, TOP_RIGHT, TOP_LEFT, BOT_LEFT, BOT_RIGHT, LEFT_TOP, LEFT_BOT, RIGHT_TOP, RIGHT_BOT, LEFT, RIGHT, TOP, BOT} SwimDir;
#define DUCK_MOVE_PIXELS 5
class Duck 
{
protected:
	std::string name;
	// Поля, необходимые для рисования утки
	HBITMAP hBmp[8];
	LONG x, y, width, height;
	SwimDir direction;

	IsFlyable* canFly;
	IsQuackable* canQuack;

	BOOL swimToPoint;
	void SwimInPt(POINT&);
public:
	Duck();
	Duck(std::string, LONG, LONG);
	Duck(const Duck&);
	virtual ~Duck();
	//////////////////////////////////////// Методы плаванья
	void Swim(HRGN&, POINT&);
	void Draw(HDC&, HDC&);
	IsFlyable* GetFlyable();
	RECT GetRedrawRect();
	RECT GetRect();
	////////////////////////////////////////
	void SetSwimToPt(BOOL);
	BOOL GetSwimToPt();
	void SetRandDir();
	void Quack(HWND&, HINSTANCE&);
	void StopQuack();
};

