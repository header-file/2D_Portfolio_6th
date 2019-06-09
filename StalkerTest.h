#pragma once
#include "GameNode.h"

struct Stalker
{
	float	x, y;
	float	angle;
	float	endX, endY;
	float	length;
	float	speed;

	RECT	rc;
};

class StalkerTest : public GameNode
{
private:
	Stalker _skr1;
	Stalker _skr2;

public:
	StalkerTest();
	~StalkerTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

