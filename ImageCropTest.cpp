#include "Game.h"
#include "ImageCropTest.h"



ImageCropTest::ImageCropTest()
{
}


ImageCropTest::~ImageCropTest()
{
}

bool ImageCropTest::Init()
{
	_background = new Image;
	_background->Init(TEXT("Image/BackGround.bmp"), WINSIZEX, WINSIZEY);

	_offsetX = _offsetY = 0;

	return true;
}

void ImageCropTest::Release()
{
	SAFE_DELETE(_background);
}

void ImageCropTest::Update()
{
	if (_offsetX <= 0)
		_offsetX = 0;
	if (_offsetY <= 0)
		_offsetY = 0;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		_offsetX -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		_offsetX += 3;
	if (KEYMANAGER->isStayKeyDown(VK_UP))
		_offsetY -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		_offsetY += 3;
}

void ImageCropTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0);
	_background->Render(hdc, 100, 100, _offsetX, _offsetY, 200, 200);
}
