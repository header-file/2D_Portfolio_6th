#include "Game.h"
#include "GameOver.h"


GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

bool GameOver::Init()
{
	backGround = IMAGEMANAGER->FindImage("GameOverPage");
	gameOver = IMAGEMANAGER->FindImage("GameOverTitle");

	pos.x = WINSIZEX / 2 - gameOver->GetWidth() / 2;
	pos.y = WINSIZEY + gameOver->GetHeight();

	return true;
}

void GameOver::Release()
{
}

void GameOver::Update()
{
	if (pos.y > WINSIZEY / 2)
		pos.y -= 5;

	if (pos.y == WINSIZEY / 2)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->Stop(TEXT("GameOverBgm"));
			SceneChange();
		}
	}
}

void GameOver::Render(HDC hdc)
{
	backGround->Render(hdc);
	gameOver->Render(hdc, pos.x, pos.y - gameOver->GetHeight() / 2);
}

void GameOver::SceneChange()
{
	SCENEMANAGER->ChangeScene(TEXT("Start"));
}
