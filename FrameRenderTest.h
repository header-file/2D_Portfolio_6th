#pragma once

class Player;
class Monster;

class FrameRenderTest : public GameNode
{
	Image* _background;
	
	Player* _player;
	Monster* _monster;
	
public:
	FrameRenderTest();
	~FrameRenderTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};

