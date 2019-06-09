#pragma once

class Animation;

class Effect
{
	Image*		_effectImage;
	Animation*	_effectAnimation;

	int			_x;
	int			_y;

	bool		_isRunning;
	float		_elapsedTime;

public:
	Effect();
	~Effect();

	bool Init(Image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	void Release();
	void Update();
	void Render(HDC hdc);

	void KillEffect();

	void StartEffect(int x, int y);
	bool GetIsRunning() { return _isRunning; }
};

