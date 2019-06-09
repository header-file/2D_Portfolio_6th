#include "Game.h"
#include "Boss.h"
#include "Bullet.h"
#include "Room9.h"


Room9::Room9()
{
}

Room9::~Room9()
{
}

bool Room9::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room9");
	sky = IMAGEMANAGER->FindImage("Sky");
	pixel = IMAGEMANAGER->FindImage("Room9pixel");

	rcWorld = { 0, 0, 1200, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect[0] = RectMake(-50, 320, 50, 200);
	doorRect[1] = RectMake(1200, 320, 50, 200);

	SetColBox();

	boss = new Boss;
	boss->Init();
	boss->SetPos({ 1000, 200 });
	
	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	isBattle = false;

	return true;
}

void Room9::Release()
{
	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room9::Update()
{
	if (boss->GetisAlive() && PLAYER->GetX() >= WINSIZEX / 2)
	{
		isBattle = true;
		boss->SetisStart(true);
	}

	CAMERA->Update();

	RoomCheck();

	CheckCollision();

	//보스
	boss->Update();
}

void Room9::Render(HDC hdc)
{
	sky->Render(hdc, -10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);

	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room9Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL || colBox[i].type == FOOTHOLD_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room9Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	//보스
	boss->Render(hdc);

	PLAYER->Render(hdc);
}

void Room9::ChangeRoom(int _number)
{
	switch (_number)
	{
	case 0:
		SCENEMANAGER->ChangeScene("R8");
		PLAYER->SetPos(2410, 500);
		MAP->ResetPosition();
		MAP->SetisHere(7);
		break;
	case 1:
		SCENEMANAGER->ChangeScene("R12");
		PLAYER->SetPos(150, 500);
		MAP->SetisFind(9);
		MAP->ResetPosition();
		MAP->SetisHere(9);
		break;
	}
}

void Room9::RoomCheck()
{
	if (!isBattle)
	{
		if (CollisionRectAndRect(doorRect[0], PLAYER->GetRect()))
			ChangeRoom(0);
		else if (CollisionRectAndRect(doorRect[1], PLAYER->GetRect()))
			ChangeRoom(1);
	}
}

void Room9::SetColBox()
{
	colBox[0].collision = RectMake(0, 0, 160, 320);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(160, 0, 880, 80);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(1040, 0, 160, 320);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(1070, 560, 130, 240);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(350, 720, 500, 80);
	colBox[4].type = RECT_COL;
	colBox[5].collision = RectMake(0, 560, 130, 240);
	colBox[5].type = RECT_COL;

	colBox[6].collision = RectMake(130, 460, 220, 340);
	colBox[6].type = PIXEL_COL;
	colBox[7].collision = RectMake(850, 460, 220, 345);
	colBox[7].type = PIXEL_COL;
}

void Room9::CheckCollision()
{
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room9Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					checkCount++;

					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);
				}
			}
			if (checkCount == 0)
			{
				if (isBattle)
				{
					if (temp.x - PLAYER->GetBoxWidth() / 2 > 0)
						PLAYER->SetPos(PLAYER->GetX() - 7, PLAYER->GetY());
				}
				else
					PLAYER->SetPos(PLAYER->GetX() - 7, PLAYER->GetY());
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			temp.x += PLAYER->GetSpeed();
			for (int i = 0; i < int(Room9Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					checkCount++;

					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);
				}
			}
			if (checkCount == 0)
			{
				if (isBattle)
				{
					if (temp.x + PLAYER->GetBoxWidth() / 2 < WINSIZEX)
						PLAYER->SetPos(PLAYER->GetX() + 7, PLAYER->GetY());
				}
				else
					PLAYER->SetPos(PLAYER->GetX() + 7, PLAYER->GetY());
			}
		}
	}

	if (PLAYER->GetState() == JUMP)
	{
		if (PLAYER->GetJumpPower() >= 0)
			temp.y -= (PLAYER->GetBoxHeight() / 2 + PLAYER->GetSpeed());
		else
			temp.y += (PLAYER->GetBoxHeight() / 2 + PLAYER->GetSpeed());

		for (int i = 0; i < int(Room9Data::ALLBOXES); i++)
		{
			if (PtInRect(&colBox[i].collision, temp))
			{
				if (colBox[i].type == FOOTHOLD_COL && PLAYER->GetJumpPower() > 0)
					continue;

				checkCount++;

				if (colBox[i].type == RECT_COL || colBox[i].type == FOOTHOLD_COL)
				{
					if (PLAYER->GetJumpPower() <= 0)
					{
						SOUNDMANAGER->Play(TEXT("Step"), 0.5f);
						PLAYER->FinJump();
					}
					else
						PLAYER->SetJumpPower(PLAYER->GetJumpPower() * -1);
				}
				else if (colBox[i].type == PIXEL_COL)
					CheckPixel(i);
			}
		}
		if (checkCount == 0)
			PLAYER->Jump();
	}
	//중력
	else
	{
		checkCount = 0;
		temp.y += (PLAYER->GetBoxHeight() / 2 + PLAYER->GetSpeed());
		for (int i = 0; i < int(Room9Data::ALLBOXES); i++)
		{
			if (PtInRect(&colBox[i].collision, temp))
			{
				checkCount++;

				if (PLAYER->GetState() == STAND)
					PLAYER->FinJump();
			}
			else
				continue;
		}
		if (checkCount == 0)
			PLAYER->Jump();
	}

	RECT tempRect;
	POINT effectPos;

	//캐릭터와 보스
	if (IntersectRect(&tempRect, &(PLAYER->GetRect()), &(boss->GetRect())))
	{
		if (boss->GetisAlive())
		{
			if (PLAYER->GetNowTime() - PLAYER->GetStandardTime() >= 1000)
			{
				effectPos.x = (tempRect.left + tempRect.right) / 2;
				effectPos.y = (tempRect.top + tempRect.bottom) / 2;

				PLAYER->Damage(boss->GetAtk(), effectPos);
			}
		}
	}

	//무기와 보스
	if (PLAYER->GetState() == ATTACK)
	{
		if (CollisionRectAndRect(PLAYER->GetHitBox(), boss->GetRect()))
		{
			if (boss->GetisAlive())
				boss->Damage(PLAYER->GetAtk());
			else
				isBattle = false;
		}	
	}

	//캐릭터와 보스의 총알
	for (int i = 0; i < int(Room9Data::MAXBOSSBULLET); i++)
	{
		if (IntersectRect(&tempRect, &(PLAYER->GetRect()), &(boss->GetBullet(i)->GetRect())))
		{
			if (boss->GetBullet(i)->GetisFire() == true)
			{
				if (PLAYER->GetNowTime() - PLAYER->GetStandardTime() >= 1000)
				{
					effectPos.x = (tempRect.left + tempRect.right) / 2;
					effectPos.y = (tempRect.top + tempRect.bottom) / 2;

					PLAYER->Damage(boss->GetAtk(), effectPos);
				}
			}
		}
	}
}

void Room9::CheckPixel(int num)
{
	int range = 15;
	switch (PLAYER->GetState())
	{
	case RUN:
		switch (PLAYER->GetDir())
		{
		case LEFT:
			for (int i = PLAYER->GetY() + PLAYER->GetImgHeight() - range; i < PLAYER->GetY() + PLAYER->GetImgHeight() + range; i++)
			{
				COLORREF color = GetPixel(pixel->GetMemDC(), PLAYER->GetX(), i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 255)
				{
					PLAYER->SetPos(PLAYER->GetX() - PLAYER->GetSpeed(), i - PLAYER->GetImgHeight());
					break;
				}
			}
			break;

		case RIGHT:
			for (int i = PLAYER->GetY() + PLAYER->GetImgHeight() - range; i < PLAYER->GetY() + PLAYER->GetImgHeight() + range; i++)
			{
				COLORREF color = GetPixel(pixel->GetMemDC(), PLAYER->GetX(), i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 255)
				{
					PLAYER->SetPos(PLAYER->GetX() + PLAYER->GetSpeed(), i - PLAYER->GetImgHeight());
					break;
				}
			}
			break;
		}
		break;
	case JUMP:
		COLORREF color = GetPixel(pixel->GetMemDC(), PLAYER->GetX(), PLAYER->GetY() + (PLAYER->GetImgHeight()));

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 255 && b == 255))
			PLAYER->FinJump();
		else
			PLAYER->Jump();
		break;
	}
}
