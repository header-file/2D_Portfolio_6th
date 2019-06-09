#include "Game.h"
#include "TimeManager.h"
#include "Timer.h"


TimeManager::TimeManager()
	: _timer(NULL)
{
}


TimeManager::~TimeManager()
{
}

bool TimeManager::Init()
{
	_timer = new Timer;
	_timer->Init();

	return true;
}

void TimeManager::Release()
{
	SAFE_DELETE(_timer);
	getSingleton()->releaseSingleton();
}

void TimeManager::Update(float lock)
{
	if (_timer != NULL)
	{
		_timer->Tick(lock);
	}
}

void TimeManager::Render(HDC hdc)
{
	TCHAR str[256] = { 0, };

	string frameRate;
	SetBkMode(hdc, TRANSPARENT);

/*#if defined(_DEBUG)
	{
		_stprintf(str, TEXT("Frame Per Sec : %d"), _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, _tcslen(str));

		_stprintf(str, TEXT("World Time : %f"), _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, _tcslen(str));

		_stprintf(str, TEXT("FElapsed Time : %f"), _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, _tcslen(str));
	}
#else
	_stprintf(str, TEXT("Frame Per Sec : %d"), _timer->getFrameRate());
	TextOut(hdc, 0, 0, str, _tcslen(str));
#endif //#if defined(_DEBUG)*/
}

float TimeManager::getElapsedTime() const
{
	return _timer->getElapsedTime();
}

float TimeManager::getWorldTime() const
{
	return _timer->getWorldTime();
}
