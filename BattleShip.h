#pragma once
class BattleShip
{
	Image*		image;
	RECT		rc;
	float		x, y;
	float		angle;
	float		speed;

public:
	BattleShip();
	~BattleShip();

	bool Init(const string imageName, int x, int y);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Draw(HDC hdc);
	void Input();
	void Move();
};

