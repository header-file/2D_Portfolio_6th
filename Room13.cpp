#include "Game.h"
#include "Room13.h"


Room13::Room13()
{
}

Room13::~Room13()
{
}

bool Room13::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room13");
	sky = IMAGEMANAGER->FindImage("Sky");
	castle = IMAGEMANAGER->FindImage("Castle");
	pixel = IMAGEMANAGER->FindImage("Room13pixel");

	rcWorld = { 0, 0, 1200, 4115 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect = RectMake(400, 4115, 300, 50);

	SetColBox();

	return true;
}

void Room13::Release()
{
}

void Room13::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();
}

void Room13::Render(HDC hdc)
{
	if (PLAYER->GetY() <= 3715 && PLAYER->GetY() >= 400)
		sky->Render(hdc, -10 - CAMERA->getPosition()->x, PLAYER->GetY() - WINSIZEY / 2 - CAMERA->getPosition()->y);
	else
	{
		sky->Render(hdc, -10 - CAMERA->getPosition()->x, 4115 - WINSIZEY - CAMERA->getPosition()->y);
		sky->Render(hdc, -10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
	}
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	for (int i = 0; i < 20; i++)
		Rectangle(hdc, collision[i].left - CAMERA->getPosition()->x, collision[i].top - CAMERA->getPosition()->y, collision[i].right - CAMERA->getPosition()->x, collision[i].bottom - CAMERA->getPosition()->y);

	HPEN hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 1, COLOR_M);
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	for (int i = 20; i < 26; i++)
		RectToLine(hdc, &collision[i], CAMERA->getPosition()->x, CAMERA->getPosition()->y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	PLAYER->Render(hdc);
}

void Room13::ChangeRoom(int _number)
{
	SCENEMANAGER->ChangeScene("R10");
	PLAYER->SetPos(400.f, 80.f);
}

void Room13::RoomCheck()
{
	if (CollisionRectAndRect(doorRect, PLAYER->GetRect()))
		ChangeRoom(0);
}

void Room13::SetColBox()
{
	collision[0] = RectMake(0, 0, 1200, 155);
	collision[1] = RectMake(0, 155, 80, 3960);
	collision[2] = RectMake(80, 355, 90, 480);
	collision[3] = RectMake(80, 1395, 80, 40);
	collision[4] = RectMake(80, 1635, 90, 480);
	collision[5] = RectMake(80, 2595, 80, 40);
	collision[6] = RectMake(80, 2835, 80, 40);
	collision[7] = RectMake(80, 3075, 720, 80);
	collision[8] = RectMake(800, 3155, 160, 40);
	collision[9] = RectMake(160, 3635, 160, 40);
	collision[10] = RectMake(80, 3875, 80, 240);
	collision[11] = RectMake(320, 4035, 240, 80);
	collision[12] = RectMake(720, 4035, 320, 80);
	collision[13] = RectMake(1040, 155, 160, 3960);
	collision[14] = RectMake(320, 3555, 720, 80);
	collision[15] = RectMake(950, 3395, 90, 240);
	collision[16] = RectMake(950, 2275, 90, 480);
	collision[17] = RectMake(960, 2035, 80, 40);
	collision[18] = RectMake(950, 995, 90, 480);
	collision[19] = RectMake(960, 755, 80, 40);

	collision[20] = RectMake(170, 355, 630, 480);
	collision[21] = RectMake(320, 995, 630, 480);
	collision[22] = RectMake(170, 1635, 630, 480);
	collision[23] = RectMake(320, 2275, 630, 480);
	collision[24] = RectMake(800, 3395, 150, 160);
	collision[25] = RectMake(160, 3875, 160, 240);
}

void Room13::CheckCollision()
{
	for (int i = 0; i < 26; i++)
	{
		if (CollisionRectAndRect(PLAYER->GetRect(), collision[i]))
		{
			if (i < 20)
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

void Room13::CheckPixel(int num)
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
