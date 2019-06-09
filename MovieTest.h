#pragma once
class MovieTest : public GameNode
{
	RECT		rc;

public:
	MovieTest();
	~MovieTest();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

