#pragma once
#include "SingletonBase.h"

#include "inc/fmod.hpp"						//fmod ����� ���� ���̺귯�� ���
#pragma comment(lib, "lib/fmodex_vc.lib")	//fmod�� wav ���ϸ� ���� ����

using namespace FMOD;

#define TOTALSOUNDBUFFER 15					//�� ���� ����� �� �ִ� ä���� ��

struct SoundInfo
{
	Sound*		sound;						//���� ����
	Channel*	channel;					//���� ����
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

