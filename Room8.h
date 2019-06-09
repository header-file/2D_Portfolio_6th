#pragma once

enum class Room8Data
{
	ALLBOXES = 6,
	MAXDOOR = 2,
	MAPWIDTH = 2560,
	MAXCANDLE = 3,
	MAXENEMY = 4,
	MAXBAT = 2,
	MAXARCHER = 1,
	MAXPERSEPHONE = 1,
	CEILINGY = 320,
	FLOORY = 720,
};

class Candle;
class Enemy;

class Room8 : public GameNode
{
private:
	Image*	backGround;
	Image*	sky;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[int(Room8Data::MAXDOOR)];
	ColBox colBox[int(Room8Data::ALLBOXES)];

	int		speed;

	Candle*	candles[int(Room8Data::MAXCANDLE)];
	Enemy*	enemy[int(Room8Data::MAXENEMY)];

	HPEN hPen, hOldPen;

public:
	Room8();
	~Room8();

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

