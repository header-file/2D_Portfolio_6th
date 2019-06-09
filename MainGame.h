#pragma once
#include "GameNode.h"


class MainGame : public GameNode
{
private:
		

public:
	MainGame();
	~MainGame();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};








/*
class MainGame : public GameNode
{
private:
Image*				_backGround;
Image*				_dogFood;



public:
MainGame();
~MainGame();

virtual bool Init();
virtual void Release();
virtual void Update();
virtual void Render(HDC hdc);


};*/

