#include "Game.h"
#include "BackBuffer.h"



BackBuffer::BackBuffer() : _backBufferInfo(NULL)
{
}


BackBuffer::~BackBuffer()
{
}

bool BackBuffer::Init(int width, int height)
{
	if (_backBufferInfo != NULL)
		Release();

	HDC hdc = GetDC(_hWnd);
	_backBufferInfo = new BackBufferInfo;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_backBufferInfo->hOldBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	if (_backBufferInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;
}

void BackBuffer::Release()
{
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		SAFE_DELETE(_backBufferInfo);
	}
}

void BackBuffer::Render(HDC hdc, int destX, int destY)
{
	//백버퍼에 출력된 내용들을 화면으로 고속 복사
	BitBlt(hdc,							//복사가 되는 DC
		destX,							//그림이 그려질 목적지(복사가 되는 위치)에 대한 좌표
		destY,
		_backBufferInfo->width,			//그릴 그림(복사가 되는 위치)에 대한 좌표
		_backBufferInfo->height,
		_backBufferInfo->hMemDC,		//그릴 그림(복사할 소스)가 있는 DC
		0,								//그릴 그림(복사할 소스)의 시작 위치
		0,
		SRCCOPY);
}
