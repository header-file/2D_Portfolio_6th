#pragma once
#include "GameNode.h"

enum class Room3Data
{
	ALLBOXES = 9,
	MAXDOOR = 2,
	MAXCANDLE = 2,
	MAPWIDTH = 2560,
	MAXENEMY = 3,
	MAXARCHER = 1,
	MAXBAT = 2,
	FLOORY = 720,
	CEILINGY = 320,
	SWORDPOSX = 2325,
	SWORDPOSY = 515,
};

class Enemy;
class Candle;

class Room3 : public GameNode
{
private:
	Image*	backGround;
	Image*	sky;
	Image*	pixel;
	Image*	sword;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[int(Room3Data::MAXDOOR)];

	ColBox colBox[int(Room3Data::ALLBOXES)];

	Candle*	candles[int(Room3Data::MAXCANDLE)];
	Enemy*	enemy[int(Room3Data::MAXENEMY)];

	HPEN	hPen, hOldPen;

	bool	isGetSword;
	POINT	swordPos;

public:
	Room3();
	~Room3();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ChangeRoom(int _number);
	void RoomCheck();
	void SetColBox();
	void CheckCollision();
	void CheckPixel(int num);
	void CheckEnemySearch(int i);
};

