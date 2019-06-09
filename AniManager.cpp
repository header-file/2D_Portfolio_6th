#include "Game.h"
#include "AniManager.h"


AniManager::AniManager()
{
}


AniManager::~AniManager()
{
}

bool AniManager::Init()
{
	return true;
}

void AniManager::Release()
{
	for (it = totalAni.begin(); it != totalAni.end(); it++)
	{
		SAFE_DELETE((it->second));
	}

	totalAni.clear();
}

void AniManager::Update()
{
	for (it = totalAni.begin(); it != totalAni.end(); it++)
	{
		if ((it->second)->isPlay())
			(it->second)->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}

void AniManager::AddDefAni(string keyName, string imageName, int fps, bool reverse, bool loop)
{
	it = totalAni.find(keyName);
	if (it != totalAni.end())
		return;

	Image* img = IMAGEMANAGER->FindImage(imageName);
	assert(img != NULL);

	Animation* ani = new Animation;

	ani->Init(img);
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	totalAni.insert({ keyName, ani });
}

void AniManager::AddArrAni(string keyName, string imageName, int* arr, int arrLen, int fps, bool loop)
{
	it = totalAni.find(keyName);
	if (it != totalAni.end())
		return;

	Image* img = IMAGEMANAGER->FindImage(imageName);
	assert(img != NULL);

	Animation* ani = new Animation;

	ani->Init(img);
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	totalAni.insert({ keyName, ani });
}

void AniManager::AddCoordAni(string keyName, string imageName, int start, int end, int fps, bool loop)
{
	it = totalAni.find(keyName);
	if (it != totalAni.end())
		return;

	Image* img = IMAGEMANAGER->FindImage(imageName);
	assert(img != NULL);

	Animation* ani = new Animation;

	ani->Init(img);
	ani->setPlayFrame(start, end, false, loop);
	ani->setFPS(fps);

	totalAni.insert({ keyName, ani });
}

void AniManager::Start(string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
		return;

	(it->second)->start();
}

void AniManager::Stop(string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
		return;

	(it->second)->stop();
}

void AniManager::Pause(string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
		return;

	(it->second)->pause();
}

void AniManager::Resume(string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
		return;

	(it->second)->resume();
}

Animation * AniManager::FindAni(string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
	{
		return (it->second);
	}

	return NULL;
}

