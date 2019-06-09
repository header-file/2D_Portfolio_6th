#pragma once
// Singleton pattern�� � Ŭ������ ���� ��ü�� �� �ϳ����� �����ؾ� �� �� ����Ѵ�.
// ���� ���������� ������ ������ ��쿡 ����Ѵ�.
// ex) � ��ü�� ���� ������ ������ ���� ���, ������ ������ �����ϴ� ��üó�� �� ���� ���� �ٷ�� �� ���� ���
// ȣ���ϴ� ������ ��ü�� �����Ǳ� ������ �ʱ�ȭ�� ���ϴ� ������ �ϱ� �����.
// �׷��⿡ Ŀ�ø� �Ǿ��ִ� ��ü���� �ʱ�ȭ ������ �ʿ信 ���� ������ ���� �����ϴ� �Լ��� �ʿ��ϴ�.

// �ʹ��� ����� ū ��ü�� ���� �� ������ ��� "�̹����� �ʹ� ũ��"�� ���� ���� �޼����� �Բ� ���尡 ���� �ʴ´�.
// Ȥ�� ó�� �ӵ��� ������ ������ �����ս��� ��������.
/*class AAA
{
private:
	static AAA * pInst;					//static���� �����ϸ� ��ü ���ΰ� �ƴ϶� ������ �������� ����
										//�׷��� private�� ����Ǿ� �־ static�ӿ��� Ŭ���� �ܺο��� ������� ���Ѵ�.

	AAA(){}
	~AAA(){}

public:
	static AAA* getInstance()
	{
		if (!pInst)
			pInst = new AAA;

		return pInst;
	}
	
	void releaseInstance()
	{

	}
};*/


//�� Ŭ������ ����ϰų�, ��ũ�η� ����� ���
template <typename T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	static T*	getSingleton();
	void		releaseSingleton();
};

template <typename T>
T* SingletonBase<T>::singleton = 0;

template <typename T>
T* SingletonBase<T>::getSingleton()
{
	if (!singleton)
		singleton = new T;

	return singleton;
}

template <typename T>
void SingletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}


//��ũ�� ��� - ������� �ȵǱ� ������ singleton patternó�� ��Ȯ�� ������ ������ �ִ� ��찡 �ƴϸ� ������� �ʴ� ���� ����.
/*#define SINGLETON_IMPLE(T) protected:\
static T* singleton;\

SingletonBase() {}\
~SingletonBase() {}\

public:\
static T*	getSingleton();\
void		releaseSingleton();\
class AAA
{
SINGLETON_IMPLE(AAA);
};*/


/*�̱��� ���̽��� Ŭ������ �����, 

1. �ش� ����� "SingletonBase.h" �߰�
2. �ش� cpp�� "Game.h"�߰�
3. Game.h�� �ش� ��� �߰�
4. Game.h�� �ش� ��ü ��ũ�� ������
*/