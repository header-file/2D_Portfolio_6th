#include "Game.h"
#include "KeyManager.h"




KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}

bool KeyManager::Init()
{
	this->getKeyUp().reset();
	this->getKeyDown().reset();

	return true;
}

void KeyManager::Release()
{
	getSingleton()->releaseSingleton();
}

bool KeyManager::isOnceKeyDown(int _key)			//이전에 눌리지 않고 현재 키가 눌렸는지만 확인
{
	if (GetAsyncKeyState(_key) & 0x8000)			//이전 상태는 상관 없이 현재 상태만을 체크하기 위해
	{
		if (!this->getKeyDown()[_key])
		{
			this->setKeyDown(_key, true);
			return true;
		}
	}
	else
		this->setKeyDown(_key, false);

	return false;
	
}

bool KeyManager::isOnceKeyUp(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		this->setKeyUp(_key, true);
	else
	{
		if (this->getKeyUp()[_key])
		{
			this->setKeyUp(_key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)		//이전에도 눌렸고 현재도 눌렸으면 true
		return true;
	
	return false;
}

bool KeyManager::isToggleKey(int _key)
{
	if (GetKeyState(_key) & 0x0001)				//누르면 on, 다시 누르면 off
		return true;

	return false;
}
