#include "Game.h"
#include "PixelCollisionTest.h"

//�׼� ���ӿ��� ĳ���Ϳ� �������� �浹 ó��?

PixelCollisionTest::PixelCollisionTest()
{
}


PixelCollisionTest::~PixelCollisionTest()
{
}

bool PixelCollisionTest::Init()
{
	_background = IMAGEMANAGER->AddImage(TEXT("Background"), TEXT("Image/background.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);
	_mountain = IMAGEMANAGER->AddImage(TEXT("Ground"), TEXT("Image/mountain.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);

	_ball = IMAGEMANAGER->AddImage(TEXT("Ball"), TEXT("Image/ball.bmp"), 60, 60, true, COLOR_M);

	_x = WINSIZEX / 2 - 150;
	_y = WINSIZEY / 2 + 400;
	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());

	_probY = _y + _ball->GetHeight() / 2;					//Ž�� �� : _y�� �������� �Ʒ� ��������ŭ

	return true;
}

void PixelCollisionTest::Release()
{
}

void PixelCollisionTest::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		_x -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		_x += 3;

	if (_x < _ball->GetWidth() / 2)
		_x = _ball->GetWidth() / 2;

	if (_x > WINSIZEX - _ball->GetWidth() / 2)
		_x = WINSIZEX - _ball->GetWidth() / 2;

	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());


	CheckCollision(_ball, _mountain, _x, _y);
	/*_probY = _y + _ball->GetHeight() / 2;

	//�ȼ��浹�� �ٽɺκ�(�ȼ����� ���� ������ ��)
	for (int i = _probY - 100; i < _probY + 100; i++)
	{
		COLORREF color = GetPixel(_mountain->GetMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->GetHeight() / 2;
			break;
		}
	}*/
}

void PixelCollisionTest::Render(HDC hdc)
{
	_background->Render(hdc);
	_mountain->Render(hdc);
	_ball->Render(hdc, _rc.left, _rc.top);
}

void PixelCollisionTest::CheckCollision(Image* pImg1, Image* pImg2, int x, int y)
{
	int _probY = y + pImg1->GetHeight() / 2;

	//�ȼ��浹�� �ٽɺκ�(�ȼ����� ���� ������ ��)
	for (int i = _probY - 100; i < _probY + 100; i++)
	{
		COLORREF color = GetPixel(pImg2->GetMemDC(), x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			pImg1->SetY(i - pImg1->GetHeight() / 2);
			break;
		}
	}
}
