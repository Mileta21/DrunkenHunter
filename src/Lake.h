#pragma once
#include "Duck.h"
class Lake
{
protected:
	std::vector<Duck*> ducks;
	HRGN hRgn;
public:
	Lake();
	virtual ~Lake();
	///////////////////////////
	void ChangeLocation();
	HRGN& GetRgn();
	void DrawLake(HDC&, HBRUSH&);
	////////////////////////// Методы доступа к уткам
	Duck* operator [](LONG);
	void AddDuck(Duck*);
	LONG GetDucksAmount();
	void DucksHaveFlown();
};

