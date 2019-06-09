#include "Game.h"
#include "Candle.h"
#include "Room12.h"


Room12::Room12()
{
}

Room12::~Room12()
{
}

bool Room12::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room12");
	pixel = IMAGEMANAGER->FindImage("Room12pixel");
	congratulateImg = IMAGEMANAGER->FindImage("Congratulations");
	congratulateAni = ANIMANAGER->FindAni("CongratulateAni");

	rcWorld = { 0, 0, 1380, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect = RectMake(-50, 320, 50, 200);

	SetColBox();

	candle = new Candle;
	candle->Init(3, 0, 0);
	candle->SetPos({ 1230, int(Room12Data::FLOORY) - candle->GetImg()->GetFrameHeight() / 2 });

	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	isGameFin = false;

	return true;
}

void Room12::Release()
{
	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room12::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();

	if (isGameFin)
	{
		if (!congratulateAni->isPlay())
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->Stop(TEXT("Bgm"));
				SCENEMANAGER->ChangeScene("Start");
			}
		}
	}
}

void Room12::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room12Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL || colBox[i].type == FOOTHOLD_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room12Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	candle->Render(hdc);
	
	PLAYER->Render(hdc);

	if (isGameFin)
		congratulateImg->AniRender(hdc, WINSIZEX / 2 - congratulateImg->GetFrameWidth() / 2, 
			WINSIZEY / 2 - congratulateImg->GetFrameHeight() / 2, congratulateAni);
}

void Room12::ChangeRoom(int _number)
{
	SCENEMANAGER->ChangeScene("R9");
	PLAYER->SetPos(1050, 500);
	MAP->ResetPosition();
	MAP->SetisHere(8);
}

void Room12::RoomCheck()
{
	if (CollisionRectAndRect(doorRect, PLAYER->GetRect()))
		ChangeRoom(0);
}

void Room12::SetColBox()
{
	colBox[0].collision = RectMake(0, 0, 160, 325);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(160, 0, 1120, 75);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(1280, 0, 100, 800);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(1230, 320, 80, 450);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(0, 565, 930, 235);
	colBox[4].type = RECT_COL;

	colBox[5].collision = RectMake(930, 220, 300, 580);
	colBox[5].type = PIXEL_COL;
}

void Room12::CheckCollision()
{
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room12Data::ALLBOXES); i++)
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
			for (int i = 0; i < int(Room12Data::ALLBOXES); i++)
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

		for (int i = 0; i < int(Room12Data::ALLBOXES); i++)
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
	//ม฿ทย
	else
	{
		checkCount = 0;
		temp.y += (PLAYER->GetBoxHeight() / 2 + PLAYER->GetSpeed());
		for (int i = 0; i < int(Room12Data::ALLBOXES); i++)
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

	//ระบา
	if (!candle->GetisBroke())
	{
		if (PLAYER->GetState() == ATTACK)
		{
			if (CollisionRectAndRect(PLAYER->GetHitBox(), candle->GetRect()))
			{
				candle->Break();
				isGameFin = true;
				ANIMANAGER->Start("CongratulateAni");
			}
		}
	}
}

void Room12::CheckPixel(int num)
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
