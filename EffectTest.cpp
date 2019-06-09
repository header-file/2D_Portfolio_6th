#include "Game.h"
#include "EffectTest.h"



EffectTest::EffectTest()
{
}


EffectTest::~EffectTest()
{
}

bool EffectTest::Init()
{
	SOUNDMANAGER->Init();

	EFFECTMANAGER->AddEffect(TEXT("Effect1"), TEXT("Image/robot_shot.bmp"),
		352, 144, 44, 72, 1, 1.0f, 10);
	EFFECTMANAGER->AddEffect(TEXT("Effect2"), TEXT("Image/wallkick.bmp"),
		180, 45, 45, 45, 5, 0.1f, 10);

	SOUNDMANAGER->AddSound(TEXT("Sound1"), TEXT("Sound/effect.wav"), false, false);

	return true;
}

void EffectTest::Release()
{
}

void EffectTest::Update()
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);
		EFFECTMANAGER->Play(TEXT("Effect1"), WINSIZEX / 2, WINSIZEY / 2);
		SOUNDMANAGER->Play(TEXT("Sound1"), 0.5f);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);
		EFFECTMANAGER->Play(TEXT("Effect2"), _ptMouse);
	}

	EFFECTMANAGER->Update();

	SOUNDMANAGER->Update();
}

void EffectTest::Render(HDC hdc)
{
	EFFECTMANAGER->Render(hdc);
}
