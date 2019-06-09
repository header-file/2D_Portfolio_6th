#pragma once
class Room13 : public GameNode
{
private:
	Image*	backGround;
	Image*	sky;
	Image*	castle;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect;
	RECT	collision[26];

public:
	Room13();
	~Room13();

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

