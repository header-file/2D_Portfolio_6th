#include "Game.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

bool SoundManager::Init()
{
	System_Create(&_system);

	if (ErrCheck(_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL)))
		return false;

	unsigned int nVersion;
	if (ErrCheck(_system->getVersion(&nVersion)))
	{
		if (nVersion != FMOD_VERSION)
			return false;
	}
	else
		return false;

	return true;
}

void SoundManager::Release()
{
	it = totalSound.begin();
	for (; it != totalSound.end(); it++)
	{
		if ((it->second)->channel)
			(it->second)->channel->stop();
		if ((it->second)->sound)
			(it->second)->sound->release();

		SAFE_DELETE((it->second));
	}

	totalSound.clear();

	if (_system)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::Update()
{
	_system->update();
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
		return;

	SoundInfo* info = new SoundInfo;
	FMOD_RESULT result;
	FMOD_MODE mode;

	if (loop)
		mode = FMOD_LOOP_NORMAL;				//루프
	else
		mode = FMOD_DEFAULT;					//한 번만 재생

	if (bgm)
		result = _system->createStream(soundName.c_str(), mode, NULL, &info->sound);
	else
		result = _system->createSound(soundName.c_str(), mode, NULL, &info->sound);

	if (!ErrCheck(result))
		return;

	totalSound.insert(make_pair(keyName, info));
}

void SoundManager::Play(string keyName, float volume)		//volume은 0~255까지. 1당 1/255(0.04)씩 올라간다고 생각하면 됨
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		if (!(it->second)->channel)
			return;

		_system->playSound(FMOD_CHANNEL_FREE, (it->second)->sound, false, &(it->second)->channel);
		(it->second)->channel->setVolume(volume);
	}
}

void SoundManager::Stop(string keyName)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->stop();
	}
}

void SoundManager::Pause(string keyName)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(true);
	}
}

void SoundManager::Resume(string keyName)
{
	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(false);
	}
}

bool SoundManager::isPlaySound(string keyName)				//채널이 15개 뿐이기 때문에 주기적으로 isPlaySound()를 통해 실행중인지 확인한 후, stop으로 만들어줘야 한다.
{
	bool isPause = false;

	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->getPaused(&isPause);
	}
	return isPause;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPlay = false;

	it = totalSound.find(keyName);
	if (it != totalSound.end())
	{
		(it->second)->channel->isPlaying(&isPlay);
	}
	return isPlay;
}

bool SoundManager::ErrCheck(FMOD_RESULT result)
{
	if(result != FMOD_OK)
		return false;

	return true;
}
