#pragma once
#include "GameNode.h"

class Player;

class CameraTest : public GameNode
{
	Image*		_background;
	Player*		_player;

	RECT		_rcWorld;
	RECT		_rcClient;
public:
	CameraTest();
	~CameraTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

