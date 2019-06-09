#pragma once

enum class Room9Data
{
	ALLBOXES = 12,
	MAXDOOR = 2,
	MAPWIDTH = 1200,
	MAXBOSSBULLET = 9,
};

class Boss;

class Room9 : public GameNode
{
private:
	Image*	backGround;
	Image*	sky;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[int(Room9Data::MAXDOOR)];

	ColBox colBox[int(Room9Data::ALLBOXES)];

	Boss*	boss;
	bool	isBattle;

	HPEN	hPen, hOldPen;

public:
	Room9();
	~Room9();

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

