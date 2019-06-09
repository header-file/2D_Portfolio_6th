#pragma once
#include "GameNode.h"

class Candle;

enum class Room1Data
{
	ALLBOXES = 7,
	MAXCANDLE = 1,
	MAPWIDTH = 6400,
	MAXZOMBIE = 6,
	FLOORY = 2400,
};

class Room1 : public GameNode
{
private:
	Image*	backGround;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect;

	ColBox colBox[(int)(Room1Data::ALLBOXES)];
	Candle*	candle;

	HPEN hPen, hOldPen;

public:
	Room1();
	~Room1();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ChangeRoom();
	void SetColBox();
	void CheckCollision();
	void CheckPixel(int num);
};

