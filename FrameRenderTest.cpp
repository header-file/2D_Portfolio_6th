#include "Game.h"
#include "FrameRenderTest.h"
#include "Player.h"
#include "Monster.h"


FrameRenderTest::FrameRenderTest()
{
}


FrameRenderTest::~FrameRenderTest()
{
}

bool FrameRenderTest::Init()
{
	//_background = new Image;
	//_background->Init(TEXT("Image/background.bmp"), WINSIZEX, WINSIZEY);

	_background = IMAGEMANAGER->AddImage(TEXT("BackGround1"), TEXT("Image/background.bmp")
		,WINSIZEX, WINSIZEY, true, RGB(255,0,255));

	//IMAGEMANAGER->AddFrameImage(TEXT("Player"), TEXT("Image/SivaRun.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage(TEXT("Monster"), TEXT("Image/Monster.bmp"), 358, 632, 2, 4, true, RGB(255, 0, 255));

	_player = new Player;
	
	_monster = new Monster;

	return true;
}

void FrameRenderTest::Release()
{
	//SAFE_DELETE(_background);
	SAFE_DELETE(_player);
	SAFE_DELETE(_monster);

	//객체 내에 release를 구현한 경우에는 _player->Release(); 로 해제
}

//프레임 스킵핑 프레임 간격을 조절.
//프레임렌더 : 이미지를 프레임 간격마다 이동시키면서 그려준다.
//일정 시간마다 이미지를 순서대로 보여줌
void FrameRenderTest::Update()
{
	_player->Update();
	
	_monster->Update();
}


//기획서 
void FrameRenderTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0);
	
	_player->Render(hdc);
	_monster->Render(hdc);
}


//객체 생성과 삭제
//new , delete
//malloc, realloc, free


//적은 자동으로 움직이고 
//플레이어의 점프처리
//너무 높지 않게 골렘을 넘을 정도로
//부딪히면 충돌처리 