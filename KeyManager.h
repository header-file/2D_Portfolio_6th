#pragma once
#include "SingletonBase.h"
#include <bitset>

using std::bitset;

#define KEYMAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	
public:
	KeyManager();
	~KeyManager();

	bool Init();
	void Release();

	bool isOnceKeyDown(int _key);
	bool isOnceKeyUp(int _key);
	bool isStayKeyDown(int _key);
	bool isToggleKey(int _key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int _key, bool _state)
	{
		_keyDown.set(_key, _state);
	}

	void setKeyUp(int _key, bool _state)
	{
		_keyUp.set(_key, _state);
	}
};

