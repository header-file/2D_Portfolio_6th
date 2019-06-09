#pragma once
#include "SingletonBase.h"

class Effect;

class EffectManager : public SingletonBase<EffectManager>
{
	typedef vector<Effect*>					vEffect;
	typedef vector<Effect*>::iterator		iEffect;

	typedef map<string, vEffect>			TotalEffect;
	typedef map<string, vEffect>::iterator	iTotalEffect;

private:

	TotalEffect			_mTotalEffect;

public:
	EffectManager();
	~EffectManager();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEffect(string effectName,
		const TCHAR* imageName,
		int imageWidth, int imageHeight,
		int effectWidth, int effectHeight,
		int fps, float elapsedTime, int buffer,
		COLORREF color = COLOR_M);

	void Play(string effectName, int x, int y);
	void Play(string effectName, POINT p);

};

