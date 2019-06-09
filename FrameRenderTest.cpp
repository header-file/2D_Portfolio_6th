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

	//��ü ���� release�� ������ ��쿡�� _player->Release(); �� ����
}

//������ ��ŵ�� ������ ������ ����.
//�����ӷ��� : �̹����� ������ ���ݸ��� �̵���Ű�鼭 �׷��ش�.
//���� �ð����� �̹����� ������� ������
void FrameRenderTest::Update()
{
	_player->Update();
	
	_monster->Update();
}


//��ȹ�� 
void FrameRenderTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0);
	
	_player->Render(hdc);
	_monster->Render(hdc);
}


//��ü ������ ����
//new , delete
//malloc, realloc, free


//���� �ڵ����� �����̰� 
//�÷��̾��� ����ó��
//�ʹ� ���� �ʰ� ���� ���� ������
//�ε����� �浹ó�� 