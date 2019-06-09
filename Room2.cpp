#include "Game.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "Candle.h"
#include "Room2.h"


Room2::Room2()
{
}

Room2::~Room2()
{
}

bool Room2::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room2");
	sky = IMAGEMANAGER->FindImage("Sky");
	wall = IMAGEMANAGER->FindImage("Wall");
	pixel = IMAGEMANAGER->FindImage("Room2pixel");

	rcWorld = { 0, 0, 6400, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect[0] = RectMake(-50, 320, 50, 200);
	doorRect[1] = RectMake(1760, -50, 300, 50);
	doorRect[2] = RectMake(6400, 320, 50, 200);

	SetColBox();

	//양초
	for (int i = 0; i < int(Room2Data::MAXCANDLE); i++)
	{
		candles[i] = new Candle;
		candles[i]->Init(2, 0, 0);
		candles[i]->SetPos({ 1280 * (i + 1), int(Room2Data::FLOORY) - candles[i]->GetImg()->GetFrameHeight() / 2 });
	}

	//적
	for (int i = 0; i < int(Room2Data::MAXENEMY); i++)
	{
		enemy[i] = new Enemy;	
		enemy[i]->Init(ZOMBIE);
		enemy[i]->SetPos({ 500 + 800 * i, int(Room2Data::FLOORY) - enemy[i]->GetImgHeight() / 2 });
	}
	
	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	return true;
}

void Room2::Release()
{
	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room2::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();

	//양초
	for (int i = 0; i < int(Room2Data::MAXCANDLE); i++)
		candles[i]->Update();

	//몬스터
	for (int i = 0; i < int(Room2Data::MAXENEMY); i++)
	{
		enemy[i]->Update();
		CheckEnemySearch(i);
	}
}

void Room2::Render(HDC hdc)
{
	if(PLAYER->GetX() <= int(Room2Data::MAPWIDTH) - WINSIZEX / 2)
		sky->Render(hdc, PLAYER->GetX() - WINSIZEX / 2 - 10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
	else
		sky->Render(hdc, int(Room2Data::MAPWIDTH) - WINSIZEX - 10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
	wall->Render(hdc, 0 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room2Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL || colBox[i].type == FOOTHOLD_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room2Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	//양초
	for (int i = 0; i < int(Room2Data::MAXCANDLE); i++)
		candles[i]->Render(hdc);

	//몬스터
	for (int i = 0; i < int(Room2Data::MAXENEMY); i++)
		enemy[i]->Render(hdc);

	//플레이어
	PLAYER->Render(hdc);
}

void Room2::ChangeRoom(int _number)
{
	switch(_number)
	{
	case 0:
		SCENEMANAGER->ChangeScene("R1");
		PLAYER->SetPos(2175, 2340);
		MAP->ResetPosition();
		MAP->SetisHere(0);
		break;
	case 1:
		SCENEMANAGER->ChangeScene("R3");
		PLAYER->SetPos(480, 650);
		MAP->SetisFind(2);
		MAP->ResetPosition();
		MAP->SetisHere(2);
		break;
	case 2:
		SCENEMANAGER->ChangeScene("R5");
		PLAYER->SetPos(120, 500);
		MAP->SetisFind(4);
		MAP->ResetPosition();
		MAP->SetisHere(4);
		break;
	}
}

void Room2::RoomCheck()
{
	if (CollisionRectAndRect(doorRect[0], PLAYER->GetRect()))
		ChangeRoom(0);
	else if (CollisionRectAndRect(doorRect[1], PLAYER->GetRect()))
		ChangeRoom(1);
	else if (CollisionRectAndRect(doorRect[2], PLAYER->GetRect()))
		ChangeRoom(2);
}

void Room2::SetColBox()
{
	colBox[0].collision = RectMake(160, 0, 1600, 80);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(0, 0, 160, 320);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(0, 560, 130, 240);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(350, 720, 5700, 80);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(6270, 560, 130, 240);
	colBox[4].type = RECT_COL;
	colBox[5].collision = RectMake(6240, 0, 160, 320);
	colBox[5].type = RECT_COL;
	colBox[6].collision = RectMake(2080, 0, 4160, 80);
	colBox[6].type = RECT_COL;

	colBox[7].collision = RectMake(1920, 120, 160, 40);
	colBox[7].type = FOOTHOLD_COL;
	colBox[8].collision = RectMake(1920, 475, 160, 40);
	colBox[8].type = FOOTHOLD_COL;
	colBox[11].collision = RectMake(1765, 295, 160, 40);
	colBox[11].type = FOOTHOLD_COL;

	colBox[9].collision = RectMake(130, 460, 220, 340);
	colBox[9].type = PIXEL_COL;
	colBox[10].collision = RectMake(6050, 460, 220, 340);
	colBox[10].type = PIXEL_COL;
}

void Room2::CheckCollision()
{
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room2Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					checkCount++;

					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);
				}
			}
			if (checkCount == 0)
				PLAYER->SetPos(PLAYER->GetX() - 7, PLAYER->GetY());
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			temp.x += PLAYER->GetSpeed();
			for (int i = 0; i < int(Room2Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					checkCount++;

					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);
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

		for (int i = 0; i < int(Room2Data::ALLBOXES); i++)
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
		for (int i = 0; i < int(Room2Data::ALLBOXES); i++)
		{
			if (PtInRect(&colBox[i].collision, temp))
			{
				checkCount++;

				if(PLAYER->GetState() == STAND)
					PLAYER->FinJump();
			}
			else
				continue;
		}
		if (checkCount == 0)
			PLAYER->Jump();
	}

	//촛불과 무기, 동전과 캐릭터
	for (int i = 0; i < int(Room2Data::MAXCANDLE); i++)
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
				for (int j = 0; j < int(Room2Data::ALLBOXES); j++)
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
	for (int i = 0; i < int(Room2Data::MAXENEMY); i++)
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
				if(PLAYER->GetState() == ATTACK)
					enemy[i]->Damage(PLAYER->GetAtk());
			}
		}

		if (enemy[i]->GetType() == PERSEPHONE)
		{
			if (IntersectRect(&tempRect, &(PLAYER->GetRect()), &(enemy[i]->GetHitBox())))
			{
				if (PLAYER->GetNowTime() - PLAYER->GetStandardTime() >= 1000)
				{
					effectPos.x = (tempRect.left + tempRect.right) / 2;
					effectPos.y = (tempRect.top + tempRect.bottom) / 2;

					if (enemy[i]->GetisAlive())
						PLAYER->Damage(enemy[i]->GetAtk(), effectPos);
				}
			}

			//적(페르세포네)과 지형
			for (int j = 0; j < int(Room2Data::ALLBOXES); j++)
			{
				if (colBox[j].type == PIXEL_COL)
				{
					if (PtInRect(&colBox[j].collision, enemy[i]->GetPos()))
					{
						switch (enemy[i]->GetDir())
						{
						case RIGHT:
							enemy[i]->SetDir(LEFT);
							enemy[i]->ChangeState(E_MOVE);
							break;
						case LEFT:
							enemy[i]->SetDir(RIGHT);
							enemy[i]->ChangeState(E_MOVE);
							break;
						}
					}
				}
			}
		}

		//적(궁수)의 총알과 캐릭터
		if (enemy[i]->GetType() == ARCHER)
		{
			if (IntersectRect(&tempRect, &(PLAYER->GetRect()), &(enemy[i]->GetBullet()->GetRect())))
			{
				if (PLAYER->GetNowTime() - PLAYER->GetStandardTime() >= 1000)
				{
					effectPos.x = (tempRect.left + tempRect.right) / 2;
					effectPos.y = (tempRect.top + tempRect.bottom) / 2;

					enemy[i]->GetBullet()->SetisFire(false);
					PLAYER->Damage(enemy[i]->GetAtk(), effectPos);
				}
			}
		}
	}
}

void Room2::CheckPixel(int num)
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

void Room2::CheckEnemySearch(int i)
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
		case ARCHER:
			if (enemy[i]->GetState() == E_MOVE)
			{
				if (PLAYER->GetPos()->y >= enemy[i]->GetPos().y - 20 && PLAYER->GetPos()->y <= enemy[i]->GetPos().y + 20)
				{
					if (!enemy[i]->GetBullet()->GetisFire())
					{
						enemy[i]->CheckDir();
						enemy[i]->ChangeState(E_ATTACK);
					}
				}
			}
			break;
		case PERSEPHONE:
			if (enemy[i]->GetState() == E_MOVE)
			{
				enemy[i]->CheckDir();
				enemy[i]->ChangeState(PERSEPHONE_BOW);
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
		case PERSEPHONE:
			if (enemy[i]->GetState() == PERSEPHONE_COMBAT)
				enemy[i]->ChangeState(E_MOVE);
			break;
		}
	}
}
