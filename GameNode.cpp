#include "Game.h"
#include "GameNode.h"
#include "Player.h"


GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

void GameNode::SetBackBuffer()
{
	_backBuffer = new BackBuffer;        //클래스 객체 동적할당
	_backBuffer->Init(WINSIZEX, WINSIZEY);
}

bool GameNode::Init()
{
	SetBackBuffer();    //리턴받기
	return true;
}

bool GameNode::Init(bool mInit)
{
	SetBackBuffer();    //리턴받기
	
	_managerInit = mInit;

	if (_managerInit)
	{
		KEYMANAGER->Init();
		TIMEMANAGER->Init();
		SOUNDMANAGER->Init();
	}

	return true;
}

void GameNode::Release()
{
	if (_managerInit)
	{
		KEYMANAGER->Release();
		TIMEMANAGER->Release();
		SOUNDMANAGER->Release();
	}
}

void GameNode::Update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void GameNode::Render(HDC hdc)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->Render(hdc);
		EndPaint(_hWnd, &ps);
		break;
	case MCIWNDM_NOTIFYPOS:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			    break;

		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	//return LRESULT();
}
