#include "Game.h"
#include "Enemy.h"
#include "Candle.h"
#include "Room5.h"


Room5::Room5()
{
}

Room5::~Room5()
{
}

bool Room5::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room5");
	pixel = IMAGEMANAGER->FindImage("Room5pixel");
	sky = IMAGEMANAGER->FindImage("Sky");

	rcWorld = { 0, 0, 2560, 2075 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect[0] = RectMake(-50, 320, 50, 200);
	doorRect[1] = RectMake(2560, 1600, 50, 200);
	doorRect[2] = RectMake(2560, 320, 50, 200);

	SetColBox();

	//적
	for (int i = 0; i < int(Room5Data::MAXENEMY); i++)
	{
		enemy[i] = new Enemy;

		if (i < int(Room5Data::MAXZOMBIE))
		{
			enemy[i]->Init(ZOMBIE);
		}		
		else
		{
			enemy[i]->Init(BAT);
		}
	}
	enemy[0]->SetPos({ 680, 1680 - enemy[0]->GetImgHeight() / 2 });
	enemy[1]->SetPos({ 1980, 1680 - enemy[1]->GetImgHeight() / 2 });
	enemy[2]->SetPos({ 1000, 640 + enemy[2]->GetImgHeight() / 2 });
	enemy[3]->SetPos({ 1975, 950 + enemy[3]->GetImgHeight() / 2 });

	//양초
	for (int i = 0; i < int(Room5Data::MAXCANDLE); i++)
	{
		candles[i] = new Candle;
		candles[i]->Init(0, 0, 0);
	}
	candles[0]->SetPos({ 1225, 235 - candles[0]->GetImg()->GetFrameHeight() / 2 });
	candles[1]->SetPos({ 1020, 1040 - candles[1]->GetImg()->GetFrameHeight() / 2 });
	candles[2]->SetPos({ 235, 1515 - candles[2]->GetImg()->GetFrameHeight() / 2 });
	candles[3]->SetPos({ 1265, 1680 - candles[3]->GetImg()->GetFrameHeight() / 2 });
	candles[4]->SetPos({ 2325, 560 - candles[4]->GetImg()->GetFrameHeight() / 2 });

	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	return true;
}

void Room5::Release()
{
	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room5::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();

	//몬스터
	for (int i = 0; i < int(Room5Data::MAXENEMY); i++)
	{
		enemy[i]->Update();
		CheckEnemySearch(i);
	}

	//양초
	for (int i = 0; i < int(Room5Data::MAXCANDLE); i++)
		candles[i]->Update();
}

void Room5::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room5Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room5Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	for (int i = 0; i < int(Room5Data::MAXENEMY); i++)
	{
		enemy[i]->Render(hdc);
	}

	for (int i = 0; i < int(Room5Data::MAXCANDLE); i++)
	{
		candles[i]->Render(hdc);
	}

	PLAYER->Render(hdc);
}

void Room5::ChangeRoom(int _number)
{
	switch (_number)
	{
	case 0:
		SCENEMANAGER->ChangeScene("R2");
		PLAYER->SetPos(6250, 500);
		MAP->ResetPosition();
		MAP->SetisHere(1);
		break;
	case 1:
		SCENEMANAGER->ChangeScene("R6");
		PLAYER->SetPos(150, 500);
		MAP->SetisFind(5);
		MAP->ResetPosition();
		MAP->SetisHere(5);
		break;
	case 2:
		SCENEMANAGER->ChangeScene("R7");
		PLAYER->SetPos(150, 500);
		MAP->SetisFind(6);
		MAP->ResetPosition();
		MAP->SetisHere(6);
		break;
	}
}

void Room5::RoomCheck()
{
	if (CollisionRectAndRect(doorRect[0], PLAYER->GetRect()))
		ChangeRoom(0);
	else if (CollisionRectAndRect(doorRect[1], PLAYER->GetRect()))
		ChangeRoom(1);
	else if (CollisionRectAndRect(doorRect[2], PLAYER->GetRect()))
		ChangeRoom(2);
}

void Room5::SetColBox()
{
	colBox[0].collision = RectMake(0, 0, 2560, 80);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(0, 80, 160, 240);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(160, 240, 160, 80);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(2400, 80, 160, 240);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(2240, 240, 160, 80);
	colBox[4].type = RECT_COL;
	colBox[5].collision = RectMake(1120, 240, 320, 1030);
	colBox[5].type = RECT_COL;
	colBox[6].collision = RectMake(0, 560, 290, 230);
	colBox[6].type = RECT_COL;
	colBox[7].collision = RectMake(290, 880, 430, 75);
	colBox[7].type = RECT_COL;
	colBox[8].collision = RectMake(2270, 560, 290, 230);
	colBox[8].type = RECT_COL;
	colBox[9].collision = RectMake(1840, 880, 560, 75);
	colBox[9].type = RECT_COL;
	colBox[10].collision = RectMake(990, 1040, 130, 230);
	colBox[10].type = RECT_COL;
	colBox[11].collision = RectMake(480, 1360, 340, 75);
	colBox[11].type = RECT_COL;
	colBox[12].collision = RectMake(1440, 1040, 130, 230);
	colBox[12].type = RECT_COL;
	colBox[13].collision = RectMake(1650, 1360, 430, 75);
	colBox[13].type = RECT_COL;
	colBox[14].collision = RectMake(0, 790, 160, 1515);
	colBox[14].type = RECT_COL;
	colBox[15].collision = RectMake(160, 1520, 170, 80);
	colBox[15].type = RECT_COL;
	colBox[16].collision = RectMake(2400, 790, 160, 810);
	colBox[16].type = RECT_COL;
	colBox[17].collision = RectMake(2240, 1440, 160, 35);
	colBox[17].type = RECT_COL;
	colBox[18].collision = RectMake(160, 1840, 130, 240);
	colBox[18].type = RECT_COL;
	colBox[19].collision = RectMake(510, 1680, 1730, 400);
	colBox[19].type = RECT_COL;
	colBox[20].collision = RectMake(2240, 1840, 320, 240);
	colBox[20].type = RECT_COL;
	colBox[21].collision = RectMake(870, 560, 960, 75);
	colBox[21].type = RECT_COL;

	colBox[22].collision = RectMake(870, 140, 280, 495);
	colBox[22].type = PIXEL_COL;
	colBox[23].collision = RectMake(1440, 140, 350, 420);
	colBox[23].type = PIXEL_COL;
	colBox[24].collision = RectMake(290, 460, 380, 420);
	colBox[24].type = PIXEL_COL;
	colBox[25].collision = RectMake(1890, 460, 380, 420);
	colBox[25].type = PIXEL_COL;
	colBox[26].collision = RectMake(610, 940, 380, 420);
	colBox[26].type = PIXEL_COL;
	colBox[27].collision = RectMake(1570, 940, 380, 420);
	colBox[27].type = PIXEL_COL;
	colBox[28].collision = RectMake(290, 1580, 220, 495);
	colBox[28].type = PIXEL_COL;
}

void Room5::CheckCollision()
{
	//지형과 캐릭터
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room5Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);

					checkCount++;
				}
			}
			if (checkCount == 0)
				PLAYER->SetPos(PLAYER->GetX() - 7, PLAYER->GetY());
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			temp.x += PLAYER->GetSpeed();
			for (int i = 0; i < int(Room5Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);

					checkCount++;					
				}
			}
			if (checkCount == 0)
				PLAYER->SetPos(PLAYER->GetX() + PLAYER->GetSpeed(), PLAYER->GetY());
		}
	}

	if (PLAYER->GetState() == JUMP)
	{
		if (PLAYER->GetJumpPower() >= 0)
			temp.y -= (PLAYER->GetBoxHeight() / 2 + PLAYER->GetSpeed());
		else
			temp.y += (PLAYER->GetBoxHeight() / 2 + PLAYER->GetSpeed());

		for (int i = 0; i < int(Room5Data::ALLBOXES); i++)
		{
			if (PtInRect(&colBox[i].collision, temp))
			{
				if (colBox[i].type == FOOTHOLD_COL && PLAYER->GetJumpPower() > 0)
					continue;

				if (colBox[i].type == PIXEL_COL)
					CheckPixel(i);
				else
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
		for (int i = 0; i < int(Room5Data::ALLBOXES); i++)
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


	//촛불과 무기, 동전과 캐릭터
	for (int i = 0; i < int(Room5Data::MAXCANDLE); i++)
	{
		if (!candles[i]->GetisBroke())
		{
			if (PLAYER->GetState() == ATTACK)
			{
				if (CollisionRectAndRect(PLAYER->GetHitBox(), candles[i]->GetRect()))
					candles[i]->Break();
			}
		}
		else
		{
			if (!candles[i]->GetisGot())
			{
				if (CollisionRectAndRect(PLAYER->GetRect(), candles[i]->GetRect()))
				{
					PLAYER->PlusGold(candles[i]->GetGold());
					candles[i]->SetisGot(true);
				}

				checkCount = 0;
				for (int j = 0; j < int(Room5Data::ALLBOXES); j++)
				{
					POINT temp = candles[i]->GetPos();
					temp.y += (candles[i]->GetImg()->GetHeight() / 2 + candles[i]->GetSpeed());
					if (PtInRect(&colBox[j].collision, temp))
						checkCount++;
				}
				if (checkCount == 0)
					candles[i]->SetPos({ candles[i]->GetPos().x, candles[i]->GetPos().y + candles[i]->GetSpeed() });
			}
		}
	}

	RECT tempRect;
	POINT effectPos;

	//적과 캐릭터, 적과 무기
	for (int i = 0; i < int(Room5Data::MAXENEMY); i++)
	{
		if (IntersectRect(&tempRect, &(PLAYER->GetRect()), &(enemy[i]->GetRect())))
		{
			if (PLAYER->GetNowTime() - PLAYER->GetStandardTime() >= 1000)
			{
				effectPos.x = (tempRect.left + tempRect.right) / 2;
				effectPos.y = (tempRect.top + tempRect.bottom) / 2;

				if (enemy[i]->GetisAlive())
					PLAYER->Damage(enemy[i]->GetAtk(), effectPos);
			}
		}

		if (CollisionRectAndRect(PLAYER->GetHitBox(), enemy[i]->GetRect()))
		{
			if (enemy[i]->GetisAlive())
			{
				if (PLAYER->GetState() == ATTACK)
					enemy[i]->Damage(PLAYER->GetAtk());
			}
		}
	}
}

void Room5::CheckPixel(int num)
{
	int range = 25;
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

void Room5::CheckEnemySearch(int i)
{
	if (PtInRect(&(enemy[i]->GetArea()), *PLAYER->GetPos()))
	{
		switch (enemy[i]->GetType())
		{
		case ZOMBIE:
			if (enemy[i]->GetState() == E_STAND)
			{
				enemy[i]->CheckDir();
				enemy[i]->ChangeState(ZOMBIE_RISEUP);
			}
			break;
		case BAT:
			if (enemy[i]->GetState() == E_STAND)
			{
				enemy[i]->CheckDir();
				enemy[i]->ChangeState(E_MOVE);
			}
			break;
		}
	}
	else
	{
		switch (enemy[i]->GetType())
		{
		case ZOMBIE:
			if (enemy[i]->GetState() == E_MOVE)
				enemy[i]->ChangeState(ZOMBIE_RISEDOWN);
			break;
		}
	}
}
