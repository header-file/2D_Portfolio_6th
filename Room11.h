#pragma once
class Room11 : public GameNode
{
private:
	Image*	backGround;
	Image*	pixel;

	RECT	rcClient;
	RECT	rcWorld;

	RECT	doorRect;
	RECT	collision[9];

public:
	Room11();
	~Room11();

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

