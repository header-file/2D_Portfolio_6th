#include "Game.h"
#include "Xml.h"
#include "Room6.h"


Room6::Room6()
{
}

Room6::~Room6()
{
}

bool Room6::Init()
{
	backGround = IMAGEMANAGER->FindImage("Room6");
	pixel = IMAGEMANAGER->FindImage("Room6pixel");

	rcWorld = { 0, 0, 1200, 800 };
	GetClientRect(_hWnd, &_rcClient);

	if (CAMERA->Init(PLAYER->GetPos(), _rcClient, rcWorld) == false)
	{
		return false;
	}

	doorRect = RectMake(-50, 320, 50, 200);

	SetColBox();

	hPen = CreatePen(PS_SOLID, 1, COLOR_M);

	return true;
}

void Room6::Release()
{
	DeleteObject(hPen);
	DeleteObject(hOldPen);
}

void Room6::Update()
{
	CAMERA->Update();

	RoomCheck();

	CheckCollision();

	Heal();
}

void Room6::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		pixel->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

		for (int i = 0; i < int(Room6Data::ALLBOXES); i++)
		{
			if (colBox[i].type == RECT_COL)
				Rectangle(hdc, colBox[i].collision.left - CAMERA->getPosition()->x, colBox[i].collision.top - CAMERA->getPosition()->y,
					colBox[i].collision.right - CAMERA->getPosition()->x, colBox[i].collision.bottom - CAMERA->getPosition()->y);
		}

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		for (int i = 0; i < int(Room6Data::ALLBOXES); i++)
		{
			if (colBox[i].type == PIXEL_COL)
				RectToLine(hdc, &colBox[i].collision, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
		}

		SelectObject(hdc, hOldPen);
	}

	PLAYER->Render(hdc);
}

void Room6::ChangeRoom(int _number)
{
	SCENEMANAGER->ChangeScene("R5");
	PLAYER->SetPos(2510, 1770);
	MAP->ResetPosition();
	MAP->SetisHere(4);
}

void Room6::RoomCheck()
{
	if (CollisionRectAndRect(doorRect, PLAYER->GetRect()))
		ChangeRoom(0);
}

void Room6::SetColBox()
{
	colBox[0].collision = RectMake(0, 0, 180, 325);
	colBox[0].type = RECT_COL;
	colBox[1].collision = RectMake(180, 0, 860, 125);
	colBox[1].type = RECT_COL;
	colBox[2].collision = RectMake(1040, 0, 160, 800);
	colBox[2].type = RECT_COL;
	colBox[3].collision = RectMake(345, 725, 510, 75);
	colBox[3].type = RECT_COL;
	colBox[4].collision = RectMake(0, 565, 130, 235);
	colBox[4].type = RECT_COL;

	colBox[5].collision = RectMake(130, 465, 215, 335);
	colBox[5].type = PIXEL_COL;
	colBox[6].collision = RectMake(855, 465, 185, 335);
	colBox[6].type = PIXEL_COL;
}

void Room6::CheckCollision()
{
	POINT temp = *PLAYER->GetPos();
	int checkCount = 0;

	if (PLAYER->GetState() == RUN || PLAYER->GetState() == JUMP)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= PLAYER->GetSpeed();
			for (int i = 0; i < int(Room6Data::ALLBOXES); i++)
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
			for (int i = 0; i < int(Room6Data::ALLBOXES); i++)
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

		for (int i = 0; i < int(Room6Data::ALLBOXES); i++)
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
		for (int i = 0; i < int(Room6Data::ALLBOXES); i++)
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

void Room6::CheckPixel(int num)
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

void Room6::Heal()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		PLAYER->SetHP(PLAYER->GetMaxHP());
		SOUNDMANAGER->Play(TEXT("Heal"), 0.5f);
		EFFECTMANAGER->Play(TEXT("HealEffect"), *PLAYER->GetPos());

		Save();
	}
}

void Room6::Save()
{
	XmlDocument* doc = new XmlDocument;
	doc->LoadFile("Save.xml");
	assert(doc != NULL);

	XmlElement* data = doc->FirstChildElement("SavedData");

	XmlElement* exp = NULL;
	exp = data->FirstChildElement();
	XmlAttribute* value = NULL;
	value = (XmlAttribute*)exp->FirstAttribute();
	value->SetAttribute(PLAYER->GetInfo()->exp);

	XmlElement* inventory = NULL;
	inventory = exp->NextSiblingElement("Inventory");
	std::string str;
	for (auto a : PLAYER->GetInventory())
	{
		if (a != 6 && a != 1)
		{
			str += std::to_string(a);
			str += ", ";
		}
	}
	inventory->SetAttribute("id", str.c_str());

	XmlElement* nowEquip = NULL;
	nowEquip = inventory->NextSiblingElement("Equipment");
	nowEquip->SetAttribute("weapon", PLAYER->GetCurWeapon());
	nowEquip->SetAttribute("armor", PLAYER->GetCurArmor());

	XmlElement*	gold = NULL;
	gold = nowEquip->NextSiblingElement("Gold");
	gold->SetAttribute("value", PLAYER->GetInfo()->gold);

	XmlElement* map = NULL;
	map = gold->NextSiblingElement("Map");
	map->SetAttribute("id", MAP->GetFindIndex().c_str());

	doc->SaveFile("Save.xml");

	delete doc;
}
