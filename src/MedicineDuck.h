#pragma once
#include "Duck.h"
class MedicineDuck :
	public Duck
{
public:
	MedicineDuck();
	MedicineDuck(std::string, HINSTANCE&, LONG, LONG);
	MedicineDuck(const MedicineDuck&);
	virtual ~MedicineDuck();
};

