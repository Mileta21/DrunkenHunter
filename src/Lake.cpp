#include "stdafx.h"
#include "Lake.h"


Lake::Lake() : hRgn(NULL)
{
}


Lake::~Lake()
{
	DeleteObject(hRgn);
}

Duck* Lake::operator[](LONG index)
{
	return ducks[index];
}

void Lake::ChangeLocation()
{
	hRgn = ScanRegion();
	OffsetRgn(hRgn, 300, -50);
}

void Lake::AddDuck(Duck* new_duck)
{
	ducks.push_back(new_duck);
}

HRGN& Lake::GetRgn()
{
	return hRgn;
}

void Lake::DrawLake(HDC& hDc, HBRUSH& hBr)
{
	FillRgn(hDc, hRgn, hBr);
}

LONG Lake::GetDucksAmount()
{
	return ducks.size();
}

void Lake::DucksHaveFlown()
{
	INT i = 0;
	for (i = GetDucksAmount() - 1; i >= 0; --i)
		if (dynamic_cast<Flyable*>(ducks[i]->GetFlyable()))
				ducks.erase(ducks.begin() + i);
}

