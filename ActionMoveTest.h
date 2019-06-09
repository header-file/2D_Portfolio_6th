#pragma once
class Action;

class ActionMoveTest : public GameNode
{
	Action*		action;

	Image*		actionImage;
	Image*		background;

	int			x, y;

public:
	ActionMoveTest();
	~ActionMoveTest();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

