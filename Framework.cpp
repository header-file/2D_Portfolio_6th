#include "Game.h"
#include "CustomDefine.h"
#include "MainGame.h"

// ���� ����:
HWND			_hWnd;
HINSTANCE		_hInst;
MainGame		_mg;

RECT			_rcClient;
POINT			_ptMouse;

void setWindowsSize(int x, int y, int width, int height);

LPCTSTR		_lpszClass = TEXT("Win32API");

static int	_nCount = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lPszCmdParam, int cmdShow)
{
	MSG							message;
	WNDCLASS					wndClass;

	_hInst = hInstance;


	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	if (!_hWnd)
		return 0;

	setWindowsSize(WINSTARTX,
					WINSTARTY,
					WINSIZEX,
					WINSIZEY);

	if (!_mg.Init())
		return 0;

	ShowWindow(_hWnd, cmdShow);

	HDC hdc = GetDC(_hWnd);

	while (true)		//������ �⺻ ���������� �޽����� �������� �ʾ�, ���Ƿ� �޼����� �ִ� ����� ����ϰ� �־���.
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))		//PeekMessage�� �޼����� ��� true�� ������, ���� ������ �����Ѵ�.(���� �����쿡���� ����)
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->Update(60.f);

			_mg.Update();
			_mg.Render(hdc);
		}
	}

	_mg.Release();
	ReleaseDC(_hWnd, hdc);

	return message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect = { 0, 0, width, height };

	//Ŭ���̾�Ʈ ������ ����� Rect(1000, 700)��ŭ���� �������ִ� ����
	AdjustWindowRect(&winRect, WINSTYLE, NULL);

	//������ ����� ���� �����쿡 �����ϴ� ����
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}