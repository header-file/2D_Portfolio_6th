#include "Game.h"
#include "Candle.h"


Candle::Candle()
{
}

Candle::~Candle()
{
}

bool Candle::Init(int _type, int _x, int _y)
{
	type = _type;

	candle4Down = NULL;

	switch (type)
	{
	case 0:
		img = IMAGEMANAGER->FindImage("Candle1");
		ani = ANIMANAGER->FindAni("Candle1Ani");

		ANIMANAGER->Start("Candle1Ani");
		break;
	case 1:
		img = IMAGEMANAGER->FindImage("Candle2");
		ani = ANIMANAGER->FindAni("Candle2Ani");

		ANIMANAGER->Start("Candle2Ani");
		break;
	case 2:
		img = IMAGEMANAGER->FindImage("Candle3");
		ani = ANIMANAGER->FindAni("Candle3Ani");

		ANIMANAGER->Start("Candle3Ani");
		break;
	case 3:
		img = IMAGEMANAGER->FindImage("Candle4");
		candle4Down = IMAGEMANAGER->FindImage("Candle4Down");
		ani = ANIMANAGER->FindAni("Candle4Ani");

		ANIMANAGER->Start("Candle4Ani");
		break;
	}
	
	light = IMAGEMANAGER->FindImage("CandleLight");
	lAni = ANIMANAGER->FindAni("LightAni");

	pos.x = _x;
	pos.y = _y;

	isBroke = false;
	isGot = false;

	colBox = RectMakeCenter(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());

	ANIMANAGER->Start("LightAni");

	gold = RAND->getFromIntoTo(1, 5) * 10;

	speed = 5;

	return false;
}

void Candle::Release()
{
}

void Candle::Update()
{
	/*if (isBroke)
			pos.y += speed;*/

	colBox = RectMakeCenter(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());

	if(isBroke)
		colBox = RectMakeCenter(pos.x, pos.y, img->GetWidth(), img->GetHeight());
}

void Candle::Render(HDC hdc)
{
	if (!isBroke)
	{
		light->AniRender(hdc, pos.x - light->GetFrameWidth() / 2 - CAMERA->getPosition()->x, 
			pos.y - (light->GetFrameHeight() + img->GetFrameHeight()) / 2 - CAMERA->getPosition()->y, lAni);
		if (candle4Down != NULL)
			candle4Down->Render(hdc, pos.x - img->GetFrameWidth() / 2 - CAMERA->getPosition()->x, pos.y - img->GetFrameHeight() / 2 - CAMERA->getPosition()->y);
		img->AniRender(hdc, pos.x - img->GetFrameWidth() / 2 - CAMERA->getPosition()->x, pos.y - img->GetFrameHeight() / 2 - CAMERA->getPosition()->y, ani);
	}
	else
	{
		if (!isGot)
		{
			if(candle4Down == NULL)
				img->Render(hdc, pos.x - img->GetWidth() / 2 - CAMERA->getPosition()->x, pos.y - img->GetHeight() / 2 - CAMERA->getPosition()->y);
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, colBox.left - CAMERA->getPosition()->x, colBox.top - CAMERA->getPosition()->y,
			colBox.right - CAMERA->getPosition()->x, colBox.bottom - CAMERA->getPosition()->y);
	}
}

void Candle::Break()
{
	isBroke = true;
	img = IMAGEMANAGER->FindImage("Coin");
}
