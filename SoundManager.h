#pragma once
#include "SingletonBase.h"

#include "inc/fmod.hpp"						//fmod 사용을 위한 라이브러리 헤더
#pragma comment(lib, "lib/fmodex_vc.lib")	//fmod는 wav 파일만 실행 가능

using namespace FMOD;

#define TOTALSOUNDBUFFER 15					//한 번에 출력할 수 있는 채널의 수

struct SoundInfo
{
	Sound*		sound;						//음원 정보
	Channel*	channel;					//상태 정보
};

class SoundManager : public SingletonBase<SoundManager>
{
private:
	System*		_system;

	map<string, SoundInfo*>				totalSound;
	map<string, SoundInfo*>::iterator	it;
public:
	SoundManager();
	~SoundManager();

	bool Init();
	void Release();
	void Update();
	void AddSound(string keyName, string soundName, bool bgm, bool loop);

	void Play(string keyName, float volume);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	bool ErrCheck(FMOD_RESULT result);
};

