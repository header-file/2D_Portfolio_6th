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

bool KeyManager::isOnceKeyDown(int _key)			//������ ������ �ʰ� ���� Ű�� ���ȴ����� Ȯ��
{
	if (GetAsyncKeyState(_key) & 0x8000)			//���� ���´� ��� ���� ���� ���¸��� üũ�ϱ� ����
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
	if (GetAsyncKeyState(_key) & 0x8000)		//�������� ���Ȱ� ���絵 �������� true
		return true;
	
	return false;
}

bool KeyManager::isToggleKey(int _key)
{
	if (GetKeyState(_key) & 0x0001)				//������ on, �ٽ� ������ off
		return true;

	return false;
}
