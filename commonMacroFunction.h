#pragma once
#include <Windows.h>


inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void RectToLine(HDC hdc, RECT* rc, LONG _x, LONG _y)
{
	int x = rc->left - _x;
	int y = rc->top - _y;
	int width = rc->right - rc->left;
	int height = rc->bottom - rc->top;

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + width, y);
	LineTo(hdc, x + width, y + height);
	LineTo(hdc, x, y + height);
	LineTo(hdc, x, y);
}

//인라인 함수는 호출하지 않고 바로 실행시키기 때문에(함수를 호출하기 위해 저장하는 과정이 없다) 자원을 적게 소모한다.
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}