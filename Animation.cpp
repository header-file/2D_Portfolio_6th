#include "Game.h"
#include "Animation.h"
#include "Image.h"


Animation::Animation()
	: _frameNum(0), _frameWidth(0), _frameHeight(0),
	_loop(false), _play(false), _nowPlayIndex(0),
	_frameUpdateSec(0), _elapsedSec(0)
{
}


Animation::~Animation()
{
}

bool Animation::Init(int totalW, int totalH, int frameW, int frameH)
{
	_frameWidth = frameW;
	
	int _frameNumWidth = totalW / _frameWidth;

	_frameHeight = frameH;

	int _frameNumHeight = totalH / _frameHeight;

	_frameNum = _frameNumWidth * _frameNumHeight;

	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;

			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	setDefPlayFrame();

	return true;
}

bool Animation::Init(Image * image)
{
	Init(image->GetWidth(), image->GetHeight(),
		image->GetFrameWidth(), image->GetFrameHeight());

	return true;
}

void Animation::Release()
{
}

void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		for (int i = 0; i < _frameNum; ++i)
		{
			_playList.push_back(i);
		}

		for (int i = _frameNum - 1; i >= 0; --i)
		{
			_playList.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < _frameNum; ++i)
		{
			_playList.push_back(i);
		}
	}
}

void Animation::setPlayFrame(int * PlayArr, int arLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	for (int i = 0; i < arLen; ++i)
		_playList.push_back(PlayArr[i]);
}

void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	if (start > end)
	{

		if (reverse)
		{
			for (int i = start; i >= end; --i)
				_playList.push_back(i);

			for (int i = end; i < start; ++i)
				_playList.push_back(i);
		}
		else
		{
			for (int i = start; i >= end; --i)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (reverse)
		{
			for (int i = start; i >= end; ++i)
				_playList.push_back(i);

			for (int i = end - 1; i > start; --i)
				_playList.push_back(i);
		}
		else
		{
			for (int i = start; i < end; ++i)
			{
				_playList.push_back(i);
			}
		}
	}
}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedSec += elapsedTime;

		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop)
					_nowPlayIndex = 0;
				else
				{
					_nowPlayIndex--;
					_play = false;
				}
			}
		}
	}
}

void Animation::start()
{
	_play = true;
	_nowPlayIndex = 0;
}

void Animation::stop()
{
	_play = false;
	_nowPlayIndex = 0;
}

void Animation::pause()
{
	_play = false;
}

void Animation::resume()
{
	_play = true;
}
