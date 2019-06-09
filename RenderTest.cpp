#include "Game.h"
#include "RenderTest.h"



RenderTest::RenderTest()
{
}


RenderTest::~RenderTest()
{
}

bool RenderTest::Init()
{
	_background1.x = 0;
	_background1.y = 0;
	_background1.image = new Image;
	_background1.image->Init(TEXT("Image/background.bmp"), WINSIZEX, WINSIZEY);
	GetClientRect(_hWnd, &drawArea);

	return true;
}

void RenderTest::Release()
{
	SAFE_DELETE(_background1.image);
}

void RenderTest::Update()
{
	_background1.x += 4;
}

void RenderTest::Render(HDC hdc)
{
	_background1.image->LoopRender(hdc, &drawArea, _background1.x, 0);
}
