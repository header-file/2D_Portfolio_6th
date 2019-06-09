#include "Game.h"
#include "CustomDefine.h"
#include "MainGame.h"

// 전역 변수:
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

	while (true)		//게임의 기본 구조에서는 메시지를 생성하지 않아, 임의로 메세지를 넣는 방식을 사용하고 있었다.
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))		//PeekMessage는 메세지가 없어도 true를 리턴해, 루프 안으로 진입한다.(데드 윈도우에서도 동작)
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

	//클라이언트 영역의 사이즈를 Rect(1000, 700)만큼으로 설정해주는 역할
	AdjustWindowRect(&winRect, WINSTYLE, NULL);

	//설정한 사이즈를 실제 윈도우에 적용하는 역할
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}