#include "Game.h"
#include "Timer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

//가변 fps 방식은 프레임 차이를 보정해주어야 한다는 부담이 있지만, 작업량이 많을 때 프레임을 낮춰 퍼포먼스 면에서 이익이 있다.
//그러나 현재 이 방식은 고정 fps를 기반으로 작성되었다.
//고정 fps이기 때문에 frame skipping으로 같은 속도로 보이게 처리해준다.

Timer::Timer()
{
}


Timer::~Timer()
{
}

bool Timer::Init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);					//현재 시간을 가져온다.

		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0.f;
	_worldTime = 0.f;

	return true;
}

void Timer::Tick(float lockFPS)
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);				//Tick이 호출될 때마다 처음 시간과 지금 시간을 비교한다. - 시간 사이의 차는 delta time이라 한다.
	}
	else
	{
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			if (_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::getFrameRate(TCHAR * str)
{
	if (str != NULL)
		_stprintf(str, TEXT("FPS : %d"), _frameRate);

	return _frameRate;
}
