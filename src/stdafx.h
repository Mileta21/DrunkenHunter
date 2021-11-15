// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000 // Контроль версии
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////v

#include "targetver.h"
// Разрешает использовать win заголовки
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <mmsystem.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
//////////////////////////////////////////^

#include <vector>
#include <string>
#include "resource.h"


#include "Lake.h"

#include "IsFlyable.h"
#include "Flyable.h"
#include "NoFlyable.h"

#include "IsQuackable.h"
#include "Quackable.h"
#include "NoQuackable.h"

#include "Duck.h"
#include "MallardDuck.h"
#include "RedHeadDuck.h"
#include "RubberDuck.h"
#include "MedicineDuck.h"

#include "Hunter.h"


LRESULT CALLBACK WFunc(HWND, UINT, WPARAM, LPARAM);
HRGN ScanRegion();
BYTE* Get24BitPixels(HBITMAP, WORD*, WORD*);
// Буфер
TCHAR str[256] = "";
#define TIMER_DUCKS_SWIM 1
#define TIMER_NEWDUCK 3
#define TIMER_HUNTER 4
#define TIMER_HUNTERCOUNTER 5
#define TIMER_QUACKING 6


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
