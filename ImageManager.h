#pragma once
#include "SingletonBase.h"

class Image;

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*>					mapImageList;
	typedef map<string, Image*>::iterator		mapImageIter;

private:
	mapImageList		_mImageList;

public:
	ImageManager();
	~ImageManager();

	bool	Init();
	void	Release();

	Image*	AddImage(string strKey, int width, int height);
	Image*	AddImage(string strKey, const TCHAR* fileName, int width, int height, bool trans, COLORREF transColor);
	Image*	AddImage(string strKey, const TCHAR* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);

	Image*	AddFrameImage(string strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image*	AddFrameImage(string strKey, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	Image*	FindImage(string strKey);

	bool	DeleteImage(string strKey);
	bool	DeleteAll();

	void	Render(string strKey, HDC hdc);
	void	Render(string strKey, HDC hdc, int destX, int destY);
	void	Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void	FrameRender(string strKey, HDC hdc, int destX, int destY);
	void	FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void	LoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

};

