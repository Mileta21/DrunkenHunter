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
		// Создание меню
		hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);
		// Создание кистей и других ресурсов
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
				// Добавим пару уток
				lake.AddDuck(new MallardDuck("MallardName", hInst, 400, 200));
				lake.AddDuck(new RedHeadDuck("RedHeadName", hInst, 400, 400));
				// Определение начального времени до появления охотника
				hunterTimer = 120000;
				counterHunter = 120;
				// Запуск таймеров
				SetTimer(hWnd, TIMER_DUCKS_SWIM, 200, NULL);
				SetTimer(hWnd, TIMER_NEWDUCK, 15000, NULL);
				SetTimer(hWnd, TIMER_HUNTER, hunterTimer, NULL);
				SetTimer(hWnd, TIMER_HUNTERCOUNTER, 1000, NULL);
				// Создание статика с отсчетом до появления охотника
				hStat = CreateWindow("static", "", WS_CHILD | WS_VISIBLE, 400, 10, 250, 30, hWnd, NULL, hInst, NULL);
				// Обозначаем, что игра началась
				bStart = TRUE;
				for (i = lake.GetDucksAmount() - 1; i >= 0; --i) // Кряканье уток
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
							lake[i]->Swim(lake.GetRgn(), pt); // Утка плывет произвольно или к точке
							InvalidateRect(hWnd, &lake[i]->GetRedrawRect(), TRUE);

							if (lake[i]->GetSwimToPt() && !counter) // Запрещаем утке плыть к точке, если время заплытия окончено
							{
								lake[i]->SetSwimToPt(FALSE);
								lake[i]->SetRandDir();
							}
						}
				if (counter)
					--counter;
				break;
		case TIMER_NEWDUCK:
			if (hunter.IsHunterAtLake()) // Если охотник на охоте, то появляются только неживые утки
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
			for (i = lake.GetDucksAmount() - 1; i >= 0; --i) // Кряканье уток
					lake[i]->Quack(hWnd, hInst);
			SetTimer(hWnd, TIMER_QUACKING, 3000, NULL);
			break;
		case TIMER_HUNTER:
			if (hunter.IsHunterAtLake())
			{
				if (hunterTimer != 30000) // Задаем новое время до появления охотника. Каждый раз на 15 секунд меньше, но время не меньше 30 секунд
				{
					hunterTimer -= 15000;
					counterHunter = hunterTimer / 1000;
				}
				SetTimer(hWnd, TIMER_HUNTER, hunterTimer, NULL);
				hunter.LeaveLake();
				InvalidateRect(hWnd, &hunter.GetRect(), TRUE); // Перерисовываем охотника
				lake.AddDuck(new MallardDuck("MallardName", hInst, 400, 200));
			}
			else // Охотник посетил озеро
			{
				SetTimer(hWnd, TIMER_HUNTER, 10000, NULL); // Переопределяем таймер на время, через которое охотник уйдет
				hunter.AttendLake();
				sprintf(str, "Охотник прибыл на озеро.");
				SendMessage(hStat, WM_SETTEXT, NULL, (LPARAM)str);

				InvalidateRect(hWnd, &hunter.GetRect(), TRUE); // Прорисовываем охотника
				lake.DucksHaveFlown(); // Живые утки улетают	
				InvalidateRgn(hWnd, lake.GetRgn(), TRUE);
			}
			break;
		case TIMER_HUNTERCOUNTER:
			if (!hunter.IsHunterAtLake())
			{
				sprintf(str, "Охотник прибудет через %d секунд.", counterHunter);
				SendMessage(hStat, WM_SETTEXT, NULL, (LPARAM)str);
				--counterHunter;
			}
			break;
		case TIMER_QUACKING:
			for (i = lake.GetDucksAmount() - 1; i >= 0; --i) // Окончание кряканья уток
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
		PostQuitMessage(0); // Корректная обработка окончания сообщения
		DeleteObject(hBrLake);
		KillTimer(hWnd, TIMER_DUCKS_SWIM);
		KillTimer(hWnd, TIMER_NEWDUCK);
		KillTimer(hWnd, TIMER_HUNTER);
		KillTimer(hWnd, TIMER_HUNTERCOUNTER);
		KillTimer(hWnd, TIMER_QUACKING);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // Возврат неотработанного сообщения
	}
	return 0L;
}

HRGN ScanRegion()
{
	HBITMAP hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_LAKE));
	BYTE transparent = 255;

	// ширина и высота битмапа
	WORD wBmpWidth, wBmpHeight;

	// конечный и временный регионы
	HRGN hRgn, hTmpRgn;

	// 24-битные пиксели из битмапа
	BYTE *pPixels = Get24BitPixels(hBmp, &wBmpWidth, &wBmpHeight);
	if (!pPixels) return NULL;

	// создаём рабочий регион
	hRgn = CreateRectRgn(0, 0, wBmpWidth, wBmpHeight);
	if (!hRgn) { delete pPixels; return NULL; }

	// ---------------------------------------------------------
	// сканируем битмап
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
				// удаляем прозрачный цвет из региона
				hTmpRgn = CreateRectRgn(x, y, x + 1, y + 1);
				CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				DeleteObject(hTmpRgn);
			}

			// следующий пиксель
			p += 3;
		}
	}

	// освобождаем пиксели
	delete pPixels;

	// возвращаем регион
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
