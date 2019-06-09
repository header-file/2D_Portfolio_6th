#pragma once

enum class Room7Data
{
	ALLBOXES = 8,
	MAXCANDLE = 2,
	MAXDOOR = 2,
	MAPWIDTH = 3840,
	MAXENEMY = 6,
	MAXZOMBIE = 2,
	MAXBAT = 2,
	MAXARCHER = 1,
	MAXPERSEPHONE = 1,
	CEILINGY = 80,
	FLOORY = 720,
};

class Candle;
class Enemy;

class Room7 : public GameNode
{
private:
	Image*	backGround;
	Image*	sky;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[int(Room7Data::MAXDOOR)];
	ColBox colBox[int(Room7Data::ALLBOXES)];

	Candle*	candles[int(Room7Data::MAXCANDLE)];
	Enemy*	enemy[int(Room7Data::MAXENEMY)];

	HPEN	hPen, hOldPen;

public:
	Room7();
	~Room7();

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

