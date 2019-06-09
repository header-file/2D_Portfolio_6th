#pragma once
#include "SingletonBase.h"

class Image;
class Animation;

class AniManager : public SingletonBase<AniManager>
{
private:
	map<string, Animation*>				totalAni;
	map<string, Animation*>::iterator	it;

public:
	AniManager();
	~AniManager();

	bool Init();
	void Release();
	void Update();

	void AddDefAni(string keyName, string imageName, int fps, bool reverse = false, bool loop = false);
	void AddArrAni(string keyName, string imageName, int* arr, int arrLen, int fps, bool loop = false);
	void AddCoordAni(string keyName, string imageName, int start, int end, int fps, bool loop = false);
	
	void Start(string key);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	Animation* FindAni(string key);
};

