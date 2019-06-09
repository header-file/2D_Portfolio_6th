#include "Game.h"
#include "ImageManager.h"



ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

bool ImageManager::Init()
{
	return true;
}

void ImageManager::Release()
{
	DeleteAll();

	getSingleton()->releaseSingleton();
}

Image * ImageManager::AddImage(string strKey, int width, int height)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddImage(string strKey, const TCHAR * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	if (FAILED(img->Init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddImage(string strKey, const TCHAR * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	if (FAILED(img->Init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddFrameImage(string strKey, const TCHAR * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	if (FAILED(img->Init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddFrameImage(string strKey, const TCHAR * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img)
		return img;

	img = new Image;
	if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

Image * ImageManager::FindImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);
	if (key != _mImageList.end())
		return key->second;

	return NULL;
}

bool ImageManager::DeleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		key->second->Release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

bool ImageManager::DeleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end(); )
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
			++iter;
	}
	_mImageList.clear();
	
	return true;
}

void ImageManager::Render(string strKey, HDC hdc)
{
	Image* img = FindImage(strKey);
	if (img)
		img->Render(hdc);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);
	if (img)
		img->Render(hdc, destX, destY);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	Image* img = FindImage(strKey);
	if (img)
		img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);
	if (img)
		img->FrameRender(hdc, destX, destY);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = FindImage(strKey);
	if (img)
		img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::LoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	Image* img = FindImage(strKey);
	if (img)
		img->LoopRender(hdc, drawArea, offsetX, offsetY);
}
