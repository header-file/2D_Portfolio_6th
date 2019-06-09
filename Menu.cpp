#include "Game.h"
#include "Menu.h"


Menu::Menu()
{
}

Menu::~Menu()
{
}

bool Menu::Init()
{
	page = IMAGEMANAGER->FindImage("MenuPage");
	arrow = IMAGEMANAGER->FindImage("SelArrow");
	atk = IMAGEMANAGER->FindImage("ATK");
	def = IMAGEMANAGER->FindImage("DEF");
	levelNumber = IMAGEMANAGER->FindImage("LevelNumber");
	stateNumber = IMAGEMANAGER->FindImage("StateNumber");

	arrowPos.x = ARROWSTARTX;
	arrowPos.y = ARROWSTARTY;

	isWeaponSel = false;
	isArmorSel = false;

	font = CreateFont(40, 0, 0, 0, 80, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("KOVERWATCH"));

	slots[0] = EQUIPMENT->GetInfo(PLAYER->GetCurWeapon())->name;
	slots[1] = EQUIPMENT->GetInfo(PLAYER->GetCurArmor())->name;

	for(int i = 0; i < MAXITEMS; i++)
		items[i] = 0;

	int i = 0;
	for (auto a : PLAYER->GetInventory())
	{
		int item = a;
		if (item <= 5)
		{
			items[i] = EQUIPMENT->GetInfo(item)->id;
			i++;
		}			
	}

	selectedId = 0;
	selectedIndex = 0;
	return true;
}

void Menu::Release()
{
	DeleteObject(font);
}

void Menu::Update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		arrowPos.y = ARROWSTARTY;
		isWeaponSel = false;
		isArmorSel = false;
		selectedId = 0;
		selectedIndex = 0;
		LoadWeaponList();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (isWeaponSel || isArmorSel)
		{
			if (selectedIndex < MAXITEMS - 1)
			{
				arrowPos.y += 80;

				selectedIndex += 2;
				selectedId = items[selectedIndex];
			}
		}
		else if (arrowPos.y < ARMORSLOTY)
		{
			arrowPos.y = ARMORSLOTY;

			LoadArmorList();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (isWeaponSel || isArmorSel)
		{
			if (selectedIndex > 1)
			{
				arrowPos.y -= 80;

				selectedIndex -= 2;
				selectedId = items[selectedIndex];
			}
		}
		else if (arrowPos.y > WEAPONSLOTY)
		{
			arrowPos.y = WEAPONSLOTY;

			LoadWeaponList();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (isWeaponSel || isArmorSel)
		{
			if (selectedIndex % 2 == 1)
			{
				arrowPos.x -= 600;

				selectedIndex--;
				selectedId = items[selectedIndex];
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (isWeaponSel || isArmorSel)
		{
			if (selectedIndex % 2 == 0)
			{
				arrowPos.x += 600;

				selectedIndex++;
				selectedId = items[selectedIndex];
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (isWeaponSel || isArmorSel)
		{
			if (isWeaponSel)
			{
				slots[0] = EQUIPMENT->GetInfo(selectedId)->name;
				PLAYER->SetCurWeapon(selectedId);
				PLAYER->WeaponChange();
			}
			else if (isArmorSel)
			{
				slots[1] = EQUIPMENT->GetInfo(selectedId)->name;
				PLAYER->SetCurArmor(selectedId);
				PLAYER->ArmorChange();
			}
		}
		else
		{
			if (arrowPos.y == WEAPONSLOTY)
			{
				isWeaponSel = true;
				selectedId = items[selectedIndex];
			}
			else if (arrowPos.y == ARMORSLOTY)
			{
				isArmorSel = true;
				selectedId = items[selectedIndex];
			}

			arrowPos.y = ITEMSELSTARTY;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (isWeaponSel == true)
		{
			isWeaponSel = false;
			arrowPos.y = WEAPONSLOTY;
			arrowPos.x = ARROWSTARTX;
			selectedIndex = 0;
			selectedId = 0;
		}
		else if (isArmorSel == true)
		{
			isArmorSel = false;
			arrowPos.y = ARMORSLOTY;
			arrowPos.x = ARROWSTARTX;
			selectedIndex = 0;
			selectedId = 0;
		}
	}
}

void Menu::Render(HDC hdc)
{
	page->Render(hdc);
	arrow->Render(hdc, arrowPos.x, arrowPos.y);

	EquipRender(hdc);
	StateRender(hdc);
}

void Menu::EquipRender(HDC hdc)
{
	//장비 슬롯의 장비명
	oldFont = (HFONT)SelectObject(hdc, font);
	oldColor = SetTextColor(hdc, RGB(255, 255, 255));

	for (int i = 0; i < MAXSLOTS; i++)
		TextOut(hdc, 100, WEAPONSLOTY + 100 * i, slots[i].c_str(), slots[i].size());

	//종류 별 장비 목록
	for (int i = 0; i < MAXITEMS; i++)
	{
		if(items[i] != 0)
			TextOut(hdc, 100 + 600 * (i % 2), 380 + 80 * (i / 2), EQUIPMENT->GetInfo(items[i])->name.c_str(), EQUIPMENT->GetInfo(items[i])->name.size());
	}

	//장비 세부 정보
	if (arrowPos.y == WEAPONSLOTY)
	{
		atk->Render(hdc, 100, 720);
		EQUIPMENT->GetInfo(PLAYER->GetCurWeapon())->icon->Render(hdc, 100, 630);

		TXTDATA->RenderNumber(hdc, EQUIPMENT->GetInfo(PLAYER->GetCurWeapon())->atk, stateNumber, 150, 720);
		TextOut(hdc, 150, 630, slots[0].c_str(), slots[0].size());
	}
	else if (arrowPos.y == ARMORSLOTY)
	{
		def->Render(hdc, 100, 720);
		EQUIPMENT->GetInfo(PLAYER->GetCurArmor())->icon->Render(hdc, 100, 630);

		TXTDATA->RenderNumber(hdc, EQUIPMENT->GetInfo(PLAYER->GetCurArmor())->def, stateNumber, 150, 720);
		TextOut(hdc, 150, 630, slots[1].c_str(), slots[1].size());
	}
	else
	{
		if (isWeaponSel)
		{
			atk->Render(hdc, 100, 720);
			EQUIPMENT->GetInfo(selectedId)->icon->Render(hdc, 100, 630);

			TXTDATA->RenderNumber(hdc, EQUIPMENT->GetInfo(selectedId)->atk, stateNumber, 150, 720);
			TextOut(hdc, 150, 630, EQUIPMENT->GetInfo(selectedId)->name.c_str(), EQUIPMENT->GetInfo(selectedId)->name.size());
		}
		else if (isArmorSel)
		{
			def->Render(hdc, 100, 720);
			EQUIPMENT->GetInfo(selectedId)->icon->Render(hdc, 100, 630);

			TXTDATA->RenderNumber(hdc, EQUIPMENT->GetInfo(selectedId)->def, stateNumber, 150, 720);
			TextOut(hdc, 150, 630, EQUIPMENT->GetInfo(selectedId)->name.c_str(), EQUIPMENT->GetInfo(selectedId)->name.size());
		}
	}

	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
}

void Menu::StateRender(HDC hdc)
{
	//스텟, 공격력
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->level, levelNumber, 300, 20);

	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->STR, stateNumber, 820, 270);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->CON, stateNumber, 820, 308);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->ATK[0], stateNumber, 820, 194);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->ATK[1], stateNumber, 1000, 194);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->DEF[0], stateNumber, 820, 232);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->DEF[1], stateNumber, 1000, 232);

	//경험치, 돈
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->exp, levelNumber, 820, 15);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->leftExp, levelNumber, 820, 65);
	TXTDATA->RenderNumber(hdc, PLAYER->GetInfo()->gold, levelNumber, 820, 120);
}

void Menu::LoadWeaponList()
{
	for (int i = 0; i < MAXITEMS; i++)
		items[i] = 0;

	int i = 0;
	for (auto a : PLAYER->GetInventory())
	{
		int item = a;
		if (item <= 5)
		{
			items[i] = EQUIPMENT->GetInfo(item)->id;
			i++;
		}
	}
}

void Menu::LoadArmorList()
{
	for (int i = 0; i < MAXITEMS; i++)
		items[i] = 0;

	int i = 0;
	for (auto a : PLAYER->GetInventory())
	{
		int item = a;
		if (item > 5)
		{
			items[i] = EQUIPMENT->GetInfo(item)->id;
			i++;
		}
	}
}
