#pragma once
class GameOver : public GameNode
{
private:
	Image* backGround;
	Image* gameOver;

	POINT	pos;

public:
	GameOver();
	~GameOver();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void SceneChange();
};

