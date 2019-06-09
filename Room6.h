#pragma once

enum class Room6Data
{
	ALLBOXES = 7,
};

class Room6 : public GameNode
{
private:
	Image*	backGround;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect;
	ColBox colBox[int(Room6Data::ALLBOXES)];

	HPEN	hPen, hOldPen;

public:
	Room6();
	~Room6();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ChangeRoom(int _number);
	void RoomCheck();
	void SetColBox();
	void CheckCollision();
	void CheckPixel(int num);
	void Heal();
	void Save();
};

