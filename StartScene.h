#pragma once
#include "GameNode.h"

enum GAME_MODE
{
	NEW_GAME = 0,
	LOAD_GAME = 1
};

#define SELECTX WINSIZEX / 2
#define SELECTY WINSIZEY - 70

class StartScene : public GameNode
{
private:
	Image*		backGround;
	Animation*	ani;
	Image*		select;

	GAME_MODE	mode;

public:
	StartScene();
	~StartScene();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void Load();
	static void SceneChange(GAME_MODE _mode);
};

