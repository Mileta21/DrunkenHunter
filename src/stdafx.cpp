// stdafx.cpp : source file that includes just the standard includes
// Sceleton.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
//

#include "stdafx.h"

extern HINSTANCE hInst;

LRESULT CALLBACK WFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, hdcm;
	PAINTSTRUCT ps;
	static HMENU hMenu;
	static HBRUSH hBrLake;
	static HWND hStat;
	static Lake lake;
	static Hunter hunter;
	LONG i = 0;
	static POINT pt;
	static LONG counter, counterHunter, hunterTimer;
	static BOOL bStart;
	switch (message)
	{
	case WM_CREATE:
		srand(time(0));
		// �������� ����
		hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);
		// �������� ������ � ������ ��������
	//	hBrLake = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WATER)));
		hBrLake = CreateSolidBrush(RGB(0, 0, 255));
		hdc = GetDC(hWnd);
		lake.ChangeLocation();
		DeleteDC(hdc);
		hunter.SetBitmap(hInst);
		break;
	case WM_LBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (PtInRegion(lake.GetRgn(), pt.x, pt.y))
		{
			for (i = lake.GetDucksAmount() - 1; i >= 0; --i)
				if (dynamic_cast<Flyable*>(lake[i]->GetFlyable()) && !PtInRect(&lake[i]->GetRect(), pt))
				{
					lake[i]->SetSwimToPt(TRUE);
				}
			counter = 5;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_STARTGAME:
			if (!bStart)
			{
				// ������� ���� ����
				lake.AddDuck(new MallardDuck("MallardName", hInst, 400, 200));
				lake.AddDuck(new RedHeadDuck("RedHeadName", hInst, 400, 400));
				// ����������� ���������� ������� �� ��������� ��������
				hunterTimer = 120000;
				counterHunter = 120;
				// ������ ��������
				SetTimer(hWnd, TIMER_DUCKS_SWIM, 200, NULL);
				SetTimer(hWnd, TIMER_NEWDUCK, 15000, NULL);
				SetTimer(hWnd, TIMER_HUNTER, hunterTimer, NULL);
				SetTimer(hWnd, TIMER_HUNTERCOUNTER, 1000, NULL);
				// �������� ������� � �������� �� ��������� ��������
				hStat = CreateWindow("static", "", WS_CHILD | WS_VISIBLE, 400, 10, 250, 30, hWnd, NULL, hInst, NULL);
				// ����������, ��� ���� ��������
				bStart = TRUE;
				for (i = lake.GetDucksAmount() - 1; i >= 0; --i) // �������� ����
					lake[i]->Quack(hWnd, hInst);
				SetTimer(hWnd, TIMER_QUACKING, 3000, NULL);
			}
			break;
		}
		break;
	case WM_TIMER:
		switch ((UINT_PTR)wParam) {
			case TIMER_DUCKS_SWIM:
				for (i = lake.GetDucksAmount() - 1; i >= 0; --i)
						{
							lake[i]->Swim(lake.GetRgn(), pt); // ���� ������ ����������� ��� � �����
							InvalidateRect(hWnd, &lake[i]->GetRedrawRect(), TRUE);

							if (lake[i]->GetSwimToPt() && !counter) // ��������� ���� ����� � �����, ���� ����� �������� ��������
							{
								lake[i]->SetSwimToPt(FALSE);
								lake[i]->SetRandDir();
							}
						}
				if (counter)
					--counter;
				break;
		case TIMER_NEWDUCK:
			if (hunter.IsHunterAtLake()) // ���� ������� �� �����, �� ���������� ������ ������� ����
				i = 2;
			else
				i = 4;
			switch (rand() % i) {
			case 0:
				lake.AddDuck(new RubberDuck("RubberName", hInst, 400, 400));
				break;
			case 1:
				lake.AddDuck(new MedicineDuck("MedicineName", hInst, 400, 350));
				break;
			case 2:
				lake.AddDuck(new RedHeadDuck("RedHeadName", hInst, 400, 400));
				break;
			case 3:
				lake.AddDuck(new MallardDuck("MallardName", hInst, 400, 200));
				break;
			}
			for (i = lake.GetDucksAmount() - 1; i >= 0; --i) // �������� ����
					lake[i]->Quack(hWnd, hInst);
			SetTimer(hWnd, TIMER_QUACKING, 3000, NULL);
			break;
		case TIMER_HUNTER:
			if (hunter.IsHunterAtLake())
			{
				if (hunterTimer != 30000) // ������ ����� ����� �� ��������� ��������. ������ ��� �� 15 ������ ������, �� ����� �� ������ 30 ������
				{
					hunterTimer -= 15000;
					counterHunter = hunterTimer / 1000;
				}
				SetTimer(hWnd, TIMER_HUNTER, hunterTimer, NULL);
				hunter.LeaveLake();
				InvalidateRect(hWnd, &hunter.GetRect(), TRUE); // �������������� ��������
				lake.AddDuck(new MallardDuck("MallardName", hInst, 400, 200));
			}
			else // ������� ������� �����
			{
				SetTimer(hWnd, TIMER_HUNTER, 10000, NULL); // �������������� ������ �� �����, ����� ������� ������� �����
				hunter.AttendLake();
				sprintf(str, "������� ������ �� �����.");
				SendMessage(hStat, WM_SETTEXT, NULL, (LPARAM)str);

				InvalidateRect(hWnd, &hunter.GetRect(), TRUE); // ������������� ��������
				lake.DucksHaveFlown(); // ����� ���� �������	
				InvalidateRgn(hWnd, lake.GetRgn(), TRUE);
			}
			break;
		case TIMER_HUNTERCOUNTER:
			if (!hunter.IsHunterAtLake())
			{
				sprintf(str, "������� �������� ����� %d ������.", counterHunter);
				SendMessage(hStat, WM_SETTEXT, NULL, (LPARAM)str);
				--counterHunter;
			}
			break;
		case TIMER_QUACKING:
			for (i = lake.GetDucksAmount() - 1; i >= 0; --i) // ��������� �������� ����
				lake[i]->StopQuack();
			InvalidateRgn(hWnd, lake.GetRgn(), TRUE);
			KillTimer(hWnd, TIMER_QUACKING);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hdcm = CreateCompatibleDC(hdc);
			lake.DrawLake(hdc, hBrLake);
		for (i = lake.GetDucksAmount() - 1; i >= 0; --i)
			lake[i]->Draw(hdc, hdcm);
		if (hunter.IsHunterAtLake())
			hunter.DrawHunter(hdc);
		EndPaint(hWnd, &ps);
		DeleteDC(hdcm);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // ���������� ��������� ��������� ���������
		DeleteObject(hBrLake);
		KillTimer(hWnd, TIMER_DUCKS_SWIM);
		KillTimer(hWnd, TIMER_NEWDUCK);
		KillTimer(hWnd, TIMER_HUNTER);
		KillTimer(hWnd, TIMER_HUNTERCOUNTER);
		KillTimer(hWnd, TIMER_QUACKING);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // ������� ��������������� ���������
	}
	return 0L;
}

HRGN ScanRegion()
{
	HBITMAP hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_LAKE));
	BYTE transparent = 255;

	// ������ � ������ �������
	WORD wBmpWidth, wBmpHeight;

	// �������� � ��������� �������
	HRGN hRgn, hTmpRgn;

	// 24-������ ������� �� �������
	BYTE *pPixels = Get24BitPixels(hBmp, &wBmpWidth, &wBmpHeight);
	if (!pPixels) return NULL;

	// ������ ������� ������
	hRgn = CreateRectRgn(0, 0, wBmpWidth, wBmpHeight);
	if (!hRgn) { delete pPixels; return NULL; }

	// ---------------------------------------------------------
	// ��������� ������
	// ---------------------------------------------------------
	DWORD p = 0;
	for (WORD y = 0; y < wBmpHeight; y++)
	{
		for (WORD x = 0; x < wBmpWidth; x++)
		{
			BYTE jRed = pPixels[p + 2];
			BYTE jGreen = pPixels[p + 1];
			BYTE jBlue = pPixels[p + 0];

			if (jRed == transparent && jGreen == transparent && jBlue == transparent)
			{
				// ������� ���������� ���� �� �������
				hTmpRgn = CreateRectRgn(x, y, x + 1, y + 1);
				CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				DeleteObject(hTmpRgn);
			}

			// ��������� �������
			p += 3;
		}
	}

	// ����������� �������
	delete pPixels;

	// ���������� ������
	return hRgn;
}

BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight)
{
	// a bitmap object just to get bitmap width and height
	BITMAP bmpBmp;

	// pointer to original bitmap info
	LPBITMAPINFO pbmiInfo;

	// bitmap info will hold the new 24bit bitmap info
	BITMAPINFO bmiInfo;

	// width and height of the bitmap
	WORD wBmpWidth, wBmpHeight;

	// ---------------------------------------------------------
	// get some info from the bitmap
	// ---------------------------------------------------------
	GetObject(pBitmap, sizeof(bmpBmp), &bmpBmp);
	pbmiInfo = (LPBITMAPINFO)&bmpBmp;

	// get width and height
	wBmpWidth = (WORD)pbmiInfo->bmiHeader.biWidth;
	wBmpWidth -= (wBmpWidth % 4);                       // width is 4 byte boundary aligned.
	wBmpHeight = (WORD)pbmiInfo->bmiHeader.biHeight;

	// copy to caller width and height parms
	*pwWidth = wBmpWidth;
	*pwHeight = wBmpHeight;
	// ---------------------------------------------------------

	  // allocate width * height * 24bits pixels
	BYTE *pPixels = new BYTE[wBmpWidth*wBmpHeight * 3];
	if (!pPixels) return NULL;

	// get user desktop device context to get pixels from
	HDC hDC = GetWindowDC(NULL);

	// fill desired structure
	bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiInfo.bmiHeader.biWidth = wBmpWidth;
	bmiInfo.bmiHeader.biHeight = -wBmpHeight;
	bmiInfo.bmiHeader.biPlanes = 1;
	bmiInfo.bmiHeader.biBitCount = 24;
	bmiInfo.bmiHeader.biCompression = BI_RGB;
	bmiInfo.bmiHeader.biSizeImage = wBmpWidth * wBmpHeight * 3;
	bmiInfo.bmiHeader.biXPelsPerMeter = 0;
	bmiInfo.bmiHeader.biYPelsPerMeter = 0;
	bmiInfo.bmiHeader.biClrUsed = 0;
	bmiInfo.bmiHeader.biClrImportant = 0;

	// get pixels from the original bitmap converted to 24bits
	int iRes = GetDIBits(hDC, pBitmap, 0, wBmpHeight, (LPVOID)pPixels, &bmiInfo, DIB_RGB_COLORS);

	// release the device context
	ReleaseDC(NULL, hDC);

	// if failed, cancel the operation.
	if (!iRes)
	{
		delete pPixels;
		return NULL;
	};

	// return the pixel array
	return pPixels;
}
