#pragma once
class IsQuackable
{
protected:
	HWND hQuack;
public:
	IsQuackable();
	virtual ~IsQuackable();
	virtual void Quack(HWND&, HINSTANCE&, POINT) = 0;
	virtual void StopQuack() = 0;
};

