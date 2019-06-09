#pragma once
#include "GameNode.h"

enum class Room2Data 
{
	ALLBOXES = 12,
	MAXCANDLE = 4,
	MAXDOOR = 3,
	MAPWIDTH = 6400,
	MAXENEMY = 6,
	FLOORY = 720,
};

class Enemy;
class Boss;
class Candle;

class Room2 : public GameNode
{
private:
	Image*	backGround;
	Image*	sky;
	Image*	wall;
	Image*	pixel;

	Enemy*	enemy[(int)(Room2Data::MAXENEMY)];
	Candle*	candles[(int)(Room2Data::MAXCANDLE)];

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[int(Room2Data::MAXDOOR)];

	ColBox colBox[(int)(Room2Data::ALLBOXES)];

	HPEN hPen, hOldPen;

public:
	Room2();
	~Room2();

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

