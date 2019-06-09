#pragma once
class Timer
{
private:
	bool	_isHardware;
	float   _timeScale;
	float   _timeElapsed;

	__int64  _curTime;
	__int64  _lastTime;
	__int64  _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSframeCount;

	float         _FPSTimeElapsed;
	float         _worldTime;

public:
	Timer();
	~Timer();

	bool Init();
	void Tick(float lockFPS = 0.0f);

	unsigned long getFrameRate(TCHAR* str = NULL);

	inline float  getElapsedTime() const { return _timeElapsed; }
	inline float  getWorldTime() const { return _worldTime; }
};

