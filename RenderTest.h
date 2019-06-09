#pragma once
#include "GameNode.h"

struct LoopObj
{
	int x;
	int y;
	Image* image;
};

class RenderTest : public GameNode
{
	LoopObj _background1;

	RECT drawArea;

public:
	RenderTest();
	~RenderTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

