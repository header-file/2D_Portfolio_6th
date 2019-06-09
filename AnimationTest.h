#pragma once
#include "GameNode.h"

class Animation;

class AnimationTest : public GameNode
{
private:
	Image *		_camel;
	Animation*  _ani1;
	Animation*  _ani2;
	Animation*  _ani3;

public:
	AnimationTest();
	~AnimationTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

