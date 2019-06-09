#pragma once

enum class Room5Data
{
	ALLBOXES = 29,
	MAXDOOR = 3,
	MAXENEMY = 4,
	MAXZOMBIE = 2,
	MAXBAT = 2,
	MAXCANDLE = 5,
};

class Enemy;
class Candle;

class Room5 : public GameNode
{
private:
	Image*	backGround;
	Image*	pixel;
	Image*	sky;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[int(Room5Data::MAXDOOR)];
	ColBox colBox[int(Room5Data::ALLBOXES)];

	Enemy*	enemy[int(Room5Data::MAXENEMY)];
	Candle*	candles[int(Room5Data::MAXCANDLE)];

	HPEN	hPen, hOldPen;

public:
	Room5();
	~Room5();

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

