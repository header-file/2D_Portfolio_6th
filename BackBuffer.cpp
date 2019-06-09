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
	//����ۿ� ��µ� ������� ȭ������ ��� ����
	BitBlt(hdc,							//���簡 �Ǵ� DC
		destX,							//�׸��� �׷��� ������(���簡 �Ǵ� ��ġ)�� ���� ��ǥ
		destY,
		_backBufferInfo->width,			//�׸� �׸�(���簡 �Ǵ� ��ġ)�� ���� ��ǥ
		_backBufferInfo->height,
		_backBufferInfo->hMemDC,		//�׸� �׸�(������ �ҽ�)�� �ִ� DC
		0,								//�׸� �׸�(������ �ҽ�)�� ���� ��ġ
		0,
		SRCCOPY);
}
