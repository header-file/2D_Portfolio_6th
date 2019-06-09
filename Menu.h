#pragma once
#include "SingletonBase.h"

#define ARROWSTARTX 50
#define ARROWSTARTY 150
#define WEAPONSLOTY 150
#define ARMORSLOTY 250
#define ITEMSELSTARTY 380
#define MAXSLOTS 2
#define MAXITEMS 5

class Menu : public SingletonBase<Menu>
{
private:
	Image*	page;
	Image*	arrow;
	Image*	atk;
	Image*	def;
	Image*	levelNumber;
	Image*	stateNumber;
	Image*	icon;

	POINT	arrowPos;

	HFONT	font, oldFont;
	COLORREF color, oldColor;

	std::string	slots[MAXSLOTS];
	int		items[MAXITEMS];

	int		selectedId;
	int		selectedIndex;

	std::vector<int> inven;

	bool	isWeaponSel;
	bool	isArmorSel;

public:
	Menu();
	~Menu();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void EquipRender(HDC hdc);
	void StateRender(HDC hdc);
	void LoadWeaponList();
	void LoadArmorList();

	//inline void SetisOpen(bool _b) { isOpen = _b; }
};