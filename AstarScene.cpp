#include "Game.h"
#include "AstarScene.h"
#include "AstarTest.h"

AstarScene::AstarScene()
{
}

AstarScene::~AstarScene()
{
}

bool AstarScene::Init()
{
	pTest = new AstarTest;
	pTest->Init();

	return true;
}

void AstarScene::Release()
{
	SAFE_DELETE(pTest);
}

void AstarScene::Update()
{
	pTest->Update();
}

void AstarScene::Render(HDC hdc)
{
	pTest->Render(hdc);
}
