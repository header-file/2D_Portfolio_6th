#include "Game.h"
#include "ActionMoveTest.h"
#include "Action.h"

ActionMoveTest::ActionMoveTest()
{
}


ActionMoveTest::~ActionMoveTest()
{
}

bool ActionMoveTest::Init()
{
	background = IMAGEMANAGER->FindImage("InGameBackGround");
	assert(background != NULL);

	action = new Action;
	action->Init();

	actionImage = IMAGEMANAGER->FindImage("Player");
	assert(actionImage != NULL);

	actionImage->SetX(WINSIZEX / 2);
	actionImage->SetY(WINSIZEY / 2);

	x = 50;
	y = 50;

	action->MoveTo(actionImage, x, y, 5.f);

	return true;
}

void ActionMoveTest::Release()
{
}

void ActionMoveTest::Update()
{
	action->Update();
}

void ActionMoveTest::Render(HDC hdc)
{
	background->Render(hdc);
	actionImage->Render(hdc, actionImage->GetX(), actionImage->GetY());
}
