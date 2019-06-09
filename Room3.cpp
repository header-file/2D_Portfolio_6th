#include "Game.h"
#include "Candle.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Room3.h"


Room3::Room3()
{
}

Room3::~Room3()
{
}

bool Room3::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room3");
	sky = IMAGEMANAGER->FindImage("Sky");
	pixel = IMAGEMANAGER->FindImage("Room3pixel");
	sword = IMAGEMANAGER->FindImage("LongSwordIcon");

	rcWorld = { 0, 0, 2560, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect[0] = RectMake(480, 800, 300, 50);
	doorRect[1] = RectMake(-50, 320, 50, 200);

	SetColBox();

	for (int i = 0; i < int(Room3Data::MAXCANDLE); i++)
	{
		candles[i] = new Candle;
		candles[i]->Init(1, 0, 0);
		candles[i]->SetPos({ 800 + 640 * i, 500 });
	}

	for (int i = 0; i < int(Room3Data::MAXENEMY); i++)
	{
		enemy[i] = new Enemy;

		if (i < int(Room3Data::MAXARCHER))
		{
			enemy[i]->Init(ARCHER);
			enemy[i]->SetPos({ 1250, int(Room3Data::FLOORY) - enemy[i]->GetImgHeight() / 2 });
		}
		else
		{
			enemy[i]->Init(BAT);
			enemy[i]->SetPos({ 300 + 1700 * i, int(Room3Data::CEILINGY) + enemy[i]->GetImgHeight() / 2 });
		}
	}

	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	if (!PLAYER->SearchItem(2))
		isGetSword = false;
	else
		isGetSword = true;
	swordPos = { int(Room3Data::SWORDPOSX), int(Room3Data::SWORDPOSY) };

	return true;
}

void Room3::Release()
{
	for (int i = 0; i < int(Room3Data::MAXCANDLE); i++)
	{
		candles[i]->Release();
		SAFE_DELETE(candles[i]);
	}

	for (int i = 0; i < int(Room3Data::MAXENEMY); i++)
	{
		enemy[i]->Release();
		SAFE_DELETE(enemy[i]);
	}

	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room3::Update()
{
	CAMERA->Update();

	//양초
	for (int i = 0; i < int(Room3Data::MAXCANDLE); i++)
		candles[i]->Update();

	//적
	for (int i = 0; i < int(Room3Data::MAXENEMY); i++)
	{
		enemy[i]->Update();
		CheckEnemySearch(i);
	}

	CheckCollision();

	RoomCheck();
}

void Room3::Render(HDC hdc)
{
	if (PLAYER->GetX() <= int(Room3Data::MAPWIDTH) - WINSIZEX / 2 && PLAYER->GetX() >= WINSIZEX / 2)
		sky->Render(hdc, PLAYER->GetX() - WINSIZEX / 2 - 10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
	else
	{
		sky->Render(hdc, int(Room3Data::MAPWIDTH) - WINSIZEX - 10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
		sky->Render(hdc, -10 - CAMERA->getPosition()->x, 0 - CAMERA->getPosition()->y);
	}
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room3Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL || colBox[i].type == FOOTHOLD_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room3Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	for (int i = 0; i < int(Room3Data::MAXCANDLE); i++)
		candles[i]->Render(hdc);

	for (int i = 0; i < int(Room3Data::MAXENEMY); i++)
		enemy[i]->Render(hdc);

	if (!isGetSword)
		sword->Render(hdc, swordPos.x - CAMERA->getPosition()->x, swordPos.y - CAMERA->getPosition()->y);

	PLAYER->Render(hdc);
}

void Room3::ChangeRoom(int _number)
{
	switch (_number)
	{
	case 0:
		SCENEMANAGER->ChangeScene("R2");
		PLAYER->SetPos(1800, 240);
		MAP->ResetPosition();
		MAP->SetisHere(1);
		break;
	case 1:
		SCENEMANAGER->ChangeScene("R4");
		PLAYER->SetPos(1050, 500);
		MAP->SetisFind(3);
		MAP->ResetPosition();
		MAP->SetisHere(3);
		break;
	}
}

void Room3::RoomCheck()
{
	if (CollisionRectAndRect(doorRect[0], PLAYER->GetRect()))
		ChangeRoom(0);
	else if (CollisionRectAndRect(doorRect[1], PLAYER->GetRect()))
		ChangeRoom(1);
}

void Room3::SetColBox()
{
	colBox[0].collision = RectMake(0, 0, 2400, 320);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(2400, 0, 160, 800);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(2105, 565, 290, 235);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(800, 720, 1090, 80);
	colBox[3].type = RECT_COL;

	colBox[4].collision = RectMake(610, 720, 190, 10);
	colBox[4].type = FOOTHOLD_COL;
	colBox[5].collision = RectMake(510, 720, 100, 10);
	colBox[5].type = FOOTHOLD_COL;

	colBox[6].collision = RectMake(0, 560, 130, 240);
	colBox[6].type = RECT_COL;

	colBox[7].collision = RectMake(130, 460, 380, 540);
	colBox[7].type = PIXEL_COL;
	colBox[8].collision = RectMake(1890, 465, 215, 535);
	colBox[8].type = PIXEL_COL;
}

void Room3::CheckCollision()
{
	//지형과 캐릭터
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room3Data::ALLBOXES); i++)
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
			for (int i = 0; i < int(Room3Data::ALLBOXES); i++)
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

		for (int i = 0; i < int(Room3Data::ALLBOXES); i++)
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
		for (int i = 0; i < int(Room3Data::ALLBOXES); i++)
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
	for (int i = 0; i < int(Room3Data::MAXCANDLE); i++)
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
				for (int j = 0; j < int(Room3Data::ALLBOXES); j++)
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
	for (int i = 0; i < int(Room3Data::MAXENEMY); i++)
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
	
	//아이템과 캐릭터
	if (PtInRect(&PLAYER->GetRect(), swordPos))
	{
		isGetSword = true;
		PLAYER->AddItem(2);
	}
}

void Room3::CheckPixel(int num)
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

void Room3::CheckEnemySearch(int i)
{
	if (PtInRect(&(enemy[i]->GetArea()), *PLAYER->GetPos()))
	{
		switch (enemy[i]->GetType())
		{
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
		}
	}
}
