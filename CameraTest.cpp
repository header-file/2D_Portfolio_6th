#include "Game.h"
#include "CameraTest.h"
#include "Player.h"



CameraTest::CameraTest()
{
}


CameraTest::~CameraTest()
{
}

bool CameraTest::Init()
{
	_background = IMAGEMANAGER->AddImage(TEXT("BackGround1"), TEXT("Image/background.bmp"), 600, 800, true, RGB(0, 0, 0));
	IMAGEMANAGER->AddFrameImage(TEXT("Player"), TEXT("Image/SivaRun.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255));

	_player = new Player;

	_rcClient = { 0, 0, WINSIZEX, WINSIZEY };
	_rcWorld = { 0, 0, 7276, 6379 };

	if (CAMERA->Init(_player->GetPos(), _rcClient, _rcWorld) == false)
	{
		return false;
	}
	
	return true;
}

void CameraTest::Release()
{
	SAFE_DELETE(_player);
}

void CameraTest::Update()
{
	_player->Update();

	CAMERA->Update();
}

void CameraTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0, CAMERA->getPosition()->x, CAMERA->getPosition()->y, WINSIZEX, WINSIZEY);

	_player->Render(hdc);
}
