#include "Game.h"
#include "AnimationTest.h"
#include "Animation.h"


AnimationTest::AnimationTest()
{
}


AnimationTest::~AnimationTest()
{
}

bool AnimationTest::Init()
{

	_camel = IMAGEMANAGER->AddFrameImage(TEXT("Camel"), TEXT("Image/camel.bmp"), 
		300, 267, 4, 3, true, RGB(255, 0, 255));
	
	_ani1 = new Animation;							//
	_ani1->Init(_camel);
	_ani1->setDefPlayFrame(false, true);			//reverse는 끝까지 오면 반대 방향으로 다음 프레임을 가져오고, loop는 끝에 도달하면 다시 처음부터 실행한다.
	_ani1->setFPS(1);

	int arrAni[] = { 1, 10, 2, 9, 3, 6 };
	_ani2 = new Animation;
	_ani2->Init(_camel);
	_ani2->setPlayFrame(arrAni, 6, false);
	_ani2->setFPS(1);

	_ani3 = new Animation;
	_ani3->Init(_camel);
	_ani3->setPlayFrame(2, 8, false, true);
	_ani3->setFPS(1);

	return true;
}

void AnimationTest::Release()
{
	SAFE_DELETE(_ani1);
	SAFE_DELETE(_ani2);
	SAFE_DELETE(_ani3);
}

void AnimationTest::Update()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
		_ani1->start();

	if (KEYMANAGER->isOnceKeyDown('W'))
		_ani2->start();
	
	if (KEYMANAGER->isOnceKeyDown('E'))
		_ani3->start();

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

}

void AnimationTest::Render(HDC hdc)
{
	_camel->AniRender(hdc, 100, 100, _ani1);
	_camel->AniRender(hdc, 100, 200, _ani2);
	_camel->AniRender(hdc, 100, 300, _ani3);
}
