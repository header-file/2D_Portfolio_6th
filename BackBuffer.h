#pragma once

class BackBuffer
{
	typedef struct tagBackBufferInfo
	{
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOldBit;
		float		x, y;
		int			width;
		int			height;

		tagBackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			x = 0.f;
			y = 0.f;
			width = 0;
			height = 0;
		}
	}BackBufferInfo, *LPBackBufferInfo;
private:
	LPBackBufferInfo _backBufferInfo;

public:
	BackBuffer();
	~BackBuffer();

	bool Init(int width, int height);
	void Release();
	void Render(HDC hdc, int destX, int destY);

	inline HDC GetMemDC() { return _backBufferInfo->hMemDC; }
};

