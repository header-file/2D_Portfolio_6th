#include "Game.h"
#include "MovieTest.h"

#pragma comment(lib, "vfw32.lib")

HWND _hWndAvi;

MovieTest::MovieTest()
{
}

MovieTest::~MovieTest()
{
}

bool MovieTest::Init()
{
	if (_hWndAvi)
	{
		MCIWndClose(_hWndAvi);
		MCIWndDestroy(_hWndAvi);
	}

	_hWndAvi = NULL;

	_hWndAvi = MCIWndCreate(_hWnd, _hInst, MCIWNDF_NOMENU | MCIWNDF_NOTIFYMODE | MCIWNDF_NOTIFYPOS | MCIWNDF_NOPLAYBAR,
		TEXT("Image/Sample_Saturn.wmv"));

	if (_hWndAvi)
	{
		GetClientRect(_hWnd, &rc);
		SetWindowPos(_hWndAvi, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER | SWP_NOMOVE);
	}

	MoveWindow(_hWndAvi, 0, 0, WINSIZEX, WINSIZEY, NULL);

	return true;
}

void MovieTest::Release()
{
}

void MovieTest::Update()
{
	//MCIWndPlayTo(_hWndAvi, MCIWndGetEnd(_hWndAvi));
	MCIWndPlay(_hWndAvi);
}

void MovieTest::Render(HDC hdc)
{
}
