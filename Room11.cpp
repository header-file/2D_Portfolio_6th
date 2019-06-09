#include "Game.h"
#include "Room11.h"


Room11::Room11()
{
}

Room11::~Room11()
{
}

bool Room11::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room11");
	pixel = IMAGEMANAGER->FindImage("Room11pixel");

	rcWorld = { 0, 0, 1200, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect = RectMake(1200, 320, 50, 200);

	SetColBox();

	return true;
}

void Room11::Release()
{
}

void Room11::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();
}

void Room11::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	for (int i = 0; i < 6; i++)
		Rectangle(hdc, collision[i].left - CAMERA->getPosition()->x, collision[i].top - CAMERA->getPosition()->y, collision[i].right - CAMERA->getPosition()->x, collision[i].bottom - CAMERA->getPosition()->y);

	HPEN hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 1, COLOR_M);
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	for (int i = 6; i < 9; i++)
		RectToLine(hdc, &collision[i], CAMERA->getPosition()->x, CAMERA->getPosition()->y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	PLAYER->Render(hdc);
}

void Room11::ChangeRoom(int _number)
{
	SCENEMANAGER->ChangeScene("R10");
	PLAYER->SetPos(50.f, 1600.f);
}

void Room11::RoomCheck()
{
	if (CollisionRectAndRect(doorRect, PLAYER->GetRect()))
		ChangeRoom(0);
}

void Room11::SetColBox()
{
	collision[0] = RectMake(0, 0, 1200, 160);
	collision[1] = RectMake(1040, 160, 160, 160);
	collision[2] = RectMake(1040, 560, 160, 240);
	collision[3] = RectMake(480, 725, 400, 75);
	collision[4] = RectMake(160, 560, 160, 240);
	collision[5] = RectMake(0, 160, 160, 640);

	collision[6] = RectMake(320, 560, 160, 240);
	collision[7] = RectMake(880, 560, 160, 240);
	collision[8] = RectMake(880, 160, 160, 160);
}

void Room11::CheckCollision()
{
	for (int i = 0; i < 9; i++)
	{
		if (CollisionRectAndRect(PLAYER->GetRect(), collision[i]))
		{
			if (i < 6)
			{
				if (PLAYER->GetX() < collision[i].left)
				{
					if (PLAYER->GetY() + PLAYER->GetImgHeight() >= collision[i].top || PLAYER->GetY() - PLAYER->GetImgHeight() <= collision[i].bottom)
						PLAYER->SetPos(PLAYER->GetX() - 7.f, PLAYER->GetY());
				}
				else if (PLAYER->GetX() > collision[i].right)
				{
					if (PLAYER->GetY() + PLAYER->GetImgHeight() >= collision[i].top || PLAYER->GetY() - PLAYER->GetImgHeight() <= collision[i].bottom)
						PLAYER->SetPos(PLAYER->GetX() + 7.f, PLAYER->GetY());
				}
				else if (PLAYER->GetY() < collision[i].top)
				{
					if (PLAYER->GetX() + PLAYER->GetImgWidth() >= collision[i].left || PLAYER->GetX() - PLAYER->GetImgWidth() <= collision[i].right)
						PLAYER->SetPos(PLAYER->GetX(), PLAYER->GetY() - 7.f);
				}
				else if (PLAYER->GetY() > collision[i].bottom)
				{
					if (PLAYER->GetX() + PLAYER->GetImgWidth() >= collision[i].left || PLAYER->GetX() - PLAYER->GetImgWidth() <= collision[i].right)
						PLAYER->SetPos(PLAYER->GetX(), PLAYER->GetY() + 7.f);
				}
			}
			else
				CheckPixel(i);
		}
	}
}

void Room11::CheckPixel(int num)
{
	switch (PLAYER->GetDir())
	{
	case LEFT:
		for (int i = PLAYER->GetY() + PLAYER->GetImgHeight() - 25; i < PLAYER->GetY() + PLAYER->GetImgHeight(); i++)
		{
			COLORREF color = GetPixel(pixel->GetMemDC(), PLAYER->GetX() - PLAYER->GetImgWidth(), i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				PLAYER->SetPos(PLAYER->GetX(), i - PLAYER->GetImgHeight());
				break;
			}
		}
		break;

	case RIGHT:
		for (int i = PLAYER->GetY() + PLAYER->GetImgHeight() - 25; i < PLAYER->GetY() + PLAYER->GetImgHeight(); i++)
		{
			COLORREF color = GetPixel(pixel->GetMemDC(), PLAYER->GetX() + PLAYER->GetImgWidth(), i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				PLAYER->SetPos(PLAYER->GetX(), i - PLAYER->GetImgHeight());
				break;
			}
		}
		break;
	}
}
