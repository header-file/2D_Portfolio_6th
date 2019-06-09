#pragma once
class ProgressBar
{
	RECT		_rcProgress;
	int			_x, _y;
	float		_width;

	Image*		_progressBarTop;
	Image*		_progressBarBottom;

public:
	ProgressBar();
	~ProgressBar();

	bool Init(int x, int y, int width, int height);
	bool Init(string strTop, string strBack, int x, int y, int width, int height);

	void Release();
	void Update();

	void Render(HDC hdc);
	void Render(HDC hdc, const POINT* pt);

	void SetGauge(float currentGauge, float maxGauge);

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
};

