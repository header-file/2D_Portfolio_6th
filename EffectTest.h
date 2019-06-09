#pragma once
#include "GameNode.h"

class EffectTest : public GameNode
{
public:
	EffectTest();
	~EffectTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

