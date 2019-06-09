#pragma once

enum class Room4Data
{
	ALLBOXES = 5,
};

#define SHOPMIN 320
#define SHOPMAX 880
#define SHOPITEMS 5

class Room4 : public GameNode
{
private:
	Image*	backGround;
	Image*	merchant;
	Animation* ani;
	Image*	shopMenu;
	Image*	menuNumber;
	Image*	selArrow;
	Image*	atk;
	Image*	def;
	Image*	gold;
	Image*	icon;
	Image*	playerGold;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect;

	ColBox colBox[int(Room4Data::ALLBOXES)];

	bool	isShopOpen;

	HFONT	font, oldFont;
	COLORREF color, oldColor;

	std::string	name[SHOPITEMS];
	int		selAtk;
	int		selDef;
	int		selPrice;

	int		arrowY;

	std::vector<int> shopList;
	std::vector<int>::iterator it;

public:
	Room4();
	~Room4();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ChangeRoom(int _number);
	void RoomCheck();
	void SetColBox();
	void CheckCollision();
	void CheckShop();
	void ShopMenu();
	void ShopRender(HDC hdc);
	void ShowInfo();
};

