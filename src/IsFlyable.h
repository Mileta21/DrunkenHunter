#pragma once
class IsFlyable
{
public:
	IsFlyable();
	virtual ~IsFlyable();
	virtual void Fly() = 0;
};

