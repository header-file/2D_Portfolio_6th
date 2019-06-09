#pragma once

enum class Room12Data
{
	ALLBOXES = 6,
	FLOORY = 320,
};

class Candle;

class Room12 : public GameNode
{
private:
	Image*	backGround;
	Image*	pixel;
	Image*	congratulateImg;
	Animation*	congratulateAni;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect;
	ColBox colBox[int(Room12Data::ALLBOXES)];

	Candle*	candle;

	HPEN	hPen, hOldPen;

	bool	isGameFin;

public:
	Room12();
	~Room12();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ChangeRoom(int _number);
	void RoomCheck();
	void SetColBox();
	void CheckCollision();
	void CheckPixel(int num);
};

