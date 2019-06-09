#include "Game.h"
#include "Candle.h"
#include "Room1.h"


Room1::Room1()
{
}


Room1::~Room1()
{
}

bool Room1::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room1");
	pixel = IMAGEMANAGER->FindImage("Room1pixel");

	rcWorld = { 0, 0, 2320, 2640 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect = RectMake(2270, 2160, 50, 200);

	SetColBox();

	//양초
	for (int i = 0; i < int(Room1Data::MAXCANDLE); i++)
	{
		candle = new Candle;
		candle->Init(0, 0, 0);

		candle->SetPos({ 1900, int(Room1Data::FLOORY) - candle->GetImg()->GetFrameHeight() / 2 });
	}

	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	return true;
}

void Room1::Release()
{
	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room1::Update()
{
	CAMERA->Update();

	CheckCollision();

	candle->Update();

	if (CollisionRectAndRect(doorRect, PLAYER->GetRect()))
		ChangeRoom();
}

void Room1::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room1Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room1Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	for (int i = 0; i < int(Room1Data::MAXCANDLE); i++)
		candle->Render(hdc);

	PLAYER->Render(hdc);
}

void Room1::ChangeRoom()
{
	SCENEMANAGER->ChangeScene("R2");
	PLAYER->SetPos(120, 500);
	MAP->SetisFind(1);
	MAP->ResetPosition();
	MAP->SetisHere(1);
}

void Room1::SetColBox()
{
	colBox[0].collision = RectMake(0, 2560, 1210, 80);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(1870, 2400, 480, 210);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(2160, 1570, 160, 590);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(1840, 1570, 320, 110);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(0, 0, 240, 1920);
	colBox[4].type = RECT_COL;

	colBox[5].collision = RectMake(240, 1600, 160, 320);
	colBox[5].type = PIXEL_COL;
	colBox[6].collision = RectMake(1210, 2330, 660, 310);
	colBox[6].type = PIXEL_COL;
}

void Room1::CheckCollision()
{
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room1Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					checkCount++;

					if (colBox[i].type == PIXEL_COL)
						CheckPixel(i);
				}
			}
			if (checkCount == 0)
				PLAYER->SetPos(PLAYER->GetX() - PLAYER->GetSpeed(), PLAYER->GetY());
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			temp.x += PLAYER->GetSpeed();
			for (int i = 0; i < int(Room1Data::ALLBOXES); i++)
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

		for (int i = 0; i < int(Room1Data::ALLBOXES); i++)
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
		for (int i = 0; i < int(Room1Data::ALLBOXES); i++)
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
	for (int i = 0; i < int(Room1Data::MAXCANDLE); i++)
	{
		if (!candle->GetisBroke())
		{
			if (PLAYER->GetState() == ATTACK)
			{
				if (CollisionRectAndRect(PLAYER->GetHitBox(), candle->GetRect()))
					candle->Break();
			}
		}
		else
		{
			if (!candle->GetisGot())
			{
				if (CollisionRectAndRect(PLAYER->GetRect(), candle->GetRect()))
				{
					PLAYER->PlusGold(candle->GetGold());
					candle->SetisGot(true);
				}

				checkCount = 0;
				for (int j = 0; j < int(Room1Data::ALLBOXES); j++)
				{
					POINT temp = candle->GetPos();
					temp.y += (candle->GetImg()->GetHeight() / 2 + candle->GetSpeed());
					if (PtInRect(&colBox[j].collision, temp))
						checkCount++;
				}
				if (checkCount == 0)
					candle->SetPos({ candle->GetPos().x, candle->GetPos().y + candle->GetSpeed() });
			}
		}
	}
}

void Room1::CheckPixel(int num)
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
