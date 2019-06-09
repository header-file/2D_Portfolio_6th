#include "Game.h"
#include "Effect.h"
#include "Animation.h"



Effect::Effect()
	: _effectImage(NULL),
	  _effectAnimation(NULL),
	  _isRunning(false), _x(0), _y(0)
{
}


Effect::~Effect()
{
}

bool Effect::Init(Image * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if(!effectImage)
		return false;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimation)
		_effectAnimation = new Animation;
	
	_effectAnimation->Init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();
}

void Effect::Release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void Effect::Update()
{
	if (!_isRunning)
		return;

	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay())
		KillEffect();
}

void Effect::Render(HDC hdc)
{
	if(!_isRunning)
		return;

	_effectImage->AniRender(hdc, _x, _y, _effectAnimation);
}

void Effect::KillEffect()
{
	_isRunning = false;
}

void Effect::StartEffect(int x, int y)
{
	if (!_effectImage || !_effectAnimation)
		return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}
