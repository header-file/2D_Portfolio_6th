#pragma once
// Singleton pattern은 어떤 클래스에 대해 객체를 단 하나만을 생성해야 할 때 사용한다.
// 또한 전역적으로 접근이 가능할 경우에 사용한다.
// ex) 어떤 객체에 대한 정보를 가지고 있을 경우, 아이템 정보를 관리하는 객체처럼 한 번만 만들어서 다루는 게 좋을 경우
// 호출하는 순간에 객체가 생성되기 때문에 초기화를 원하는 순간에 하기 힘들다.
// 그렇기에 커플링 되어있는 객체들의 초기화 순서를 필요에 의한 순서로 정해 실행하는 함수가 필요하다.

// 너무나 사이즈가 큰 객체를 여러 번 생성할 경우 "이미지가 너무 크다"는 식의 에러 메세지와 함께 빌드가 되지 않는다.
// 혹은 처리 속도가 떨어져 게임의 퍼포먼스가 떨어진다.
/*class AAA
{
private:
	static AAA * pInst;					//static으로 선언하면 객체 내부가 아니라 데이터 영역에서 생성
										//그러나 private로 선언되어 있어서 static임에도 클래스 외부에서 사용하지 못한다.

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


//이 클래스를 상속하거나, 매크로로 만들어 사용
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


//매크로 사용 - 디버깅이 안되기 때문에 singleton pattern처럼 명확히 형식이 정해져 있는 경우가 아니면 사용하지 않는 편이 좋다.
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


/*싱글턴 베이스의 클래스를 만들시, 

1. 해당 헤더에 "SingletonBase.h" 추가
2. 해당 cpp에 "Game.h"추가
3. Game.h에 해당 헤더 추가
4. Game.h에 해당 객체 매크로 디파인
*/