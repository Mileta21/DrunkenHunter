#pragma once
class Hunter
{
protected:
	HBITMAP hBmp;
	LONG width, height;
	std::string name;
	bool onTheHunt;
public:
	Hunter();
	Hunter(std::string, bool, HINSTANCE&);
	Hunter(const Hunter&);
	virtual ~Hunter();
	/////////////////
	void AttendLake();
	void LeaveLake();
	bool IsHunterAtLake();
	//////////////////
	void SetBitmap(HINSTANCE&);
	RECT GetRect();
	void DrawHunter(HDC&);
};

