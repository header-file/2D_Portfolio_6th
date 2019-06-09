#pragma once
#include "GameNode.h"

class PixelCollisionTest : public GameNode
{
	Image*		_background;
	Image*		_mountain;
	Image*		_ball;

	RECT		_rc;
	float		_x, _y;
	int			_probY;
public:
	PixelCollisionTest();
	~PixelCollisionTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckCollision(Image* pImg1, Image* pImg2, int x, int y);
};

