#include "Game.h"
#include "Room4.h"


Room4::Room4()
{
}

Room4::~Room4()
{
}

bool Room4::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room4");
	merchant = IMAGEMANAGER->FindImage("Merchant");
	ani = ANIMANAGER->FindAni("MerchantAni");
	shopMenu = IMAGEMANAGER->FindImage("ShopMenu");
	selArrow = IMAGEMANAGER->FindImage("SelArrow");
	menuNumber = IMAGEMANAGER->FindImage("MenuNumber");
	atk = IMAGEMANAGER->FindImage("ATK");
	def = IMAGEMANAGER->FindImage("DEF");
	gold = IMAGEMANAGER->FindImage("Gold");
	icon = IMAGEMANAGER->FindImage("SpearIcon");
	playerGold = IMAGEMANAGER->FindImage("StateNumber");

	rcWorld = { 0, 0, 1200, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect = RectMake(1200, 320, 50, 200);

	ANIMANAGER->Start("MerchantAni");

	SetColBox();

	shopList.push_back(EQUIPMENT->GetInfo(3)->id);
	shopList.push_back(EQUIPMENT->GetInfo(5)->id);
	shopList.push_back(EQUIPMENT->GetInfo(7)->id);
	shopList.push_back(EQUIPMENT->GetInfo(8)->id);
	shopList.push_back(EQUIPMENT->GetInfo(9)->id);

	it = shopList.begin();

	arrowY = 100;
	selAtk = 15;
	selDef = 0;
	selPrice = 500;

	isShopOpen = false;

	font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("KOVERWATCH"));

	return true;
}

void Room4::Release()
{
}

void Room4::Update()
{
	if (!isShopOpen)
	{
		CAMERA->Update();

		RoomCheck();

		CheckCollision();

		CheckShop();
	}
	else
		ShopMenu();
}

void Room4::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	merchant->AniRender(hdc, WINSIZEX / 2 - merchant->GetFrameWidth() / 2, 645 - merchant->GetFrameHeight(), ani);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < int(Room4Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}
	}

	PLAYER->Render(hdc);

	if (isShopOpen)
		ShopRender(hdc);
}

void Room4::ChangeRoom(int _number)
{
	SCENEMANAGER->ChangeScene("R3");
	PLAYER->SetPos(150, 500);
	MAP->ResetPosition();
	MAP->SetisHere(2);
}

void Room4::RoomCheck()
{
	if (CollisionRectAndRect(doorRect, PLAYER->GetRect()))
		ChangeRoom(0);
}

void Room4::SetColBox()
{
	colBox[0].collision = RectMake(0, 0, 160, 800);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(160, 0, 880, 80);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(1040, 0, 160, 320);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(1040, 560, 160, 240);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(160, 720, 880, 80);
	colBox[4].type = RECT_COL;
}

void Room4::CheckCollision()
{
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room4Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
					checkCount++;
				}
			}
			if (checkCount == 0)
				PLAYER->SetPos(PLAYER->GetX() - 7, PLAYER->GetY());
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			temp.x += PLAYER->GetSpeed();
			for (int i = 0; i < int(Room4Data::ALLBOXES); i++)
			{
				if (PtInRect(&colBox[i].collision, temp))
				{
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

		for (int i = 0; i < int(Room4Data::ALLBOXES); i++)
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
		for (int i = 0; i < int(Room4Data::ALLBOXES); i++)
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
}

void Room4::CheckShop()
{
	if (PLAYER->GetX() >= SHOPMIN && PLAYER->GetX() <= SHOPMAX)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			isShopOpen = true;
			PLAYER->SetisMovable(false);

			int i = 0;
			for (auto n : shopList)
			{
				name[i] = EQUIPMENT->GetInfo(n)->name;
				i++;
			}
			it = shopList.begin();
		}
	}
}

void Room4::ShopMenu()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{	
		if (it != shopList.end())
		{
			if (arrowY < 500)
			{
				it++;

				arrowY += 80;

				ShowInfo();
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (it != shopList.begin())
		{
			it--;
			arrowY -= 80;

			ShowInfo();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		int price = EQUIPMENT->GetInfo(*it)->price;
		if (PLAYER->GetGold() >= price)
			PLAYER->Buy(*it, price);
		else
			SOUNDMANAGER->Play(TEXT("Back"), 0.5f);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		PLAYER->SetisMovable(true);
		isShopOpen = false;
	}
}

void Room4::ShopRender(HDC hdc)
{
	shopMenu->Render(hdc);

	selArrow->Render(hdc, 100, arrowY);

	oldFont = (HFONT)SelectObject(hdc, font);
	oldColor = SetTextColor(hdc, RGB(255, 255, 255));

	for(int i = 0; i < shopList.capacity(); i++)
		TextOut(hdc, 140, 100 + 80 * i, name[i].c_str(), name[i].size());

	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);

	icon->Render(hdc, 100, 620);

	if (selAtk != 0)
	{
		atk->Render(hdc, 200, 650);
		TXTDATA->RenderNumber(hdc, selAtk, menuNumber, 250, 650);
	}
	else
	{
		def->Render(hdc, 200, 650);
		TXTDATA->RenderNumber(hdc, selDef, menuNumber, 250, 650);
	}

	gold->Render(hdc, 400, 650);
	TXTDATA->RenderNumber(hdc, selPrice, menuNumber, 430, 650);

	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->gold, playerGold, 950, 50);
}

void Room4::ShowInfo()
{
	selAtk = EQUIPMENT->GetInfo(*it)->atk;
	selDef = EQUIPMENT->GetInfo(*it)->def;
	selPrice = EQUIPMENT->GetInfo(*it)->price;
	icon = EQUIPMENT->GetInfo(*it)->icon;
}