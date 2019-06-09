#pragma once
class Room10 : public GameNode
{
	Image*	backGround;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect[4];
	RECT	collision[20];

public:
	Room10();
	~Room10();

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

