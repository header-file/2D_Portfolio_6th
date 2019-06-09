#include "Game.h"
#include "Room10.h"


Room10::Room10()
{
}

Room10::~Room10()
{
}

bool Room10::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room10");
	pixel = IMAGEMANAGER->FindImage("Room10pixel");

	rcWorld = { 0, 0, 1200, 2075 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect[0] = RectMake(-50, 320, 50, 200);
	doorRect[1] = RectMake(-50, 1600, 50, 200);
	doorRect[2] = RectMake(1200, 1600, 50, 200);
	doorRect[3] = RectMake(400, -50, 300, 50);

	SetColBox();

	return true;
}

void Room10::Release()
{
}

void Room10::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();
}

void Room10::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	for (int i = 0; i < 12; i++)
		Rectangle(hdc, collision[i].left - CAMERA->getPosition()->x, collision[i].top - CAMERA->getPosition()->y, collision[i].right - CAMERA->getPosition()->x, collision[i].bottom - CAMERA->getPosition()->y);

	HPEN hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 1, COLOR_M);
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	for (int i = 12; i < 20; i++)
		RectToLine(hdc, &collision[i], CAMERA->getPosition()->x, CAMERA->getPosition()->y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	PLAYER->Render(hdc);
}

void Room10::ChangeRoom(int _number)
{
	switch (_number)
	{
	case 0:
		SCENEMANAGER->ChangeScene("R9");
		PLAYER->SetPos(2510.f, 320.f);
		break;
	case 1:
		SCENEMANAGER->ChangeScene("R11");
		PLAYER->SetPos(1150.f, 320.f);
		break;
	case 2:
		SCENEMANAGER->ChangeScene("R12");
		PLAYER->SetPos(50.f, 320.f);
		break;
	case 3:
		SCENEMANAGER->ChangeScene("R13");
		PLAYER->SetPos(475.f, 3880.f);
		break;
	}
}

void Room10::RoomCheck()
{
	if (CollisionRectAndRect(doorRect[0], PLAYER->GetRect()))
		ChangeRoom(0);
	else if (CollisionRectAndRect(doorRect[1], PLAYER->GetRect()))
		ChangeRoom(1);
	else if (CollisionRectAndRect(doorRect[2], PLAYER->GetRect()))
		ChangeRoom(2);
	else if (CollisionRectAndRect(doorRect[3], PLAYER->GetRect()))
		ChangeRoom(3);
}

void Room10::SetColBox()
{
	collision[0] = RectMake(0, 0, 400, 320);
	collision[1] = RectMake(0, 560, 160, 1015);
	collision[2] = RectMake(160, 720, 160, 550);
	collision[3] = RectMake(0, 1840, 340, 235);
	collision[4] = RectMake(480, 2000, 400, 75);
	collision[5] = RectMake(1040, 1840, 160, 235);
	collision[6] = RectMake(560, 1680, 260, 80);		//160?
	collision[7] = RectMake(1040, 790, 160, 810);
	collision[8] = RectMake(950, 0, 250, 800);
	collision[9] = RectMake(640, 80, 80, 80);
	collision[10] = RectMake(640, 400, 80, 80);
	collision[11] = RectMake(560, 880, 250, 80);		//80?

	collision[12] = RectMake(720, 0, 230, 230);
	collision[13] = RectMake(330, 240, 310, 240);
	collision[14] = RectMake(640, 560, 310, 400);
	collision[15] = RectMake(320, 1040, 320, 400);
	collision[16] = RectMake(720, 1360, 320, 400);
	collision[17] = RectMake(340, 1840, 140, 235);
	collision[18] = RectMake(880, 1840, 160, 235);
	collision[19] = RectMake(160, 560, 160, 160);
}

void Room10::CheckCollision()
{
	for (int i = 0; i < 20; i++)
	{
		if (CollisionRectAndRect(PLAYER->GetRect(), collision[i]))
		{
			if (i < 12)
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

void Room10::CheckPixel(int num)
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
