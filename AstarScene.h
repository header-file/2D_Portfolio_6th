#pragma once

class AstarTest;

class AstarScene : public GameNode
{
	AstarTest*		pTest;

public:
	AstarScene();
	~AstarScene();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

