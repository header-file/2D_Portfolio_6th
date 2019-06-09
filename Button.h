#pragma once

enum BUTTONDIR
{
	BUTTONDIR_NONE,
	BUTTONDIR_UP,
	BUTTONDIR_DOWN,
};

typedef void(*FUNC)();
//typedef std::function<void(*)()> pFunc;


class Button
{
	BUTTONDIR		_direction;

	string			_imageName;
	Image*			_image;
	RECT			_rc;
	float			_x, _y;
	POINT			_btnDownFramePoint;
	POINT			_btnUpFramePoint;

	FUNC			_callBackFunc;
public:
	Button();
	~Button();

	bool Init(const string imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, FUNC pFunc);
	void Release();
	void Update();
	void Render(HDC hdc);
};

//함수 포인터
/*
CALLBACK 함수를 쓸 때 / 임의의 CALLBACK 함수를 만들 때 사용
CALLBACK 함수는 함수를 직접 호출하는 것이 아니라 특정한 상황이 되면 OS가 호출(백그라운드에서 호출)

함수를 사용하기 위해서는 함수명과 매개변수가 필요하다.
그러나 언제 어디서 함수를 사용할지 모르면 마땅한 헤더를 추가하기가 비효율적이다.
그래서 함수를 따로 저장해 포인터를 통해 언제 어디서든 사용할 수 있게 한 것이 함수 포인터

반환형 (*함수명)(매개변수 리스트);

typedef void *Func(int);		//반환형이 void*인 일반 함수
typedef void(*Func)(int);		//함수 포인터 자료형 선언
Func pFunc = function;			//함수포인터형 변수 = 함수명 (괄호 없는 함수명)
선언된 함수포인터는 함수 형태로 사용 가능
(*pFunc)(10) 형태로 사용하는 것이 함수 포인터를 함수 형태로 사용하는 원칙적인 방법이나,
pFunc(10) 형태의 호출도 허용된다.

함수 호출시에 함수 선언부로 가기 전에 매개변수를 스택에 저장하고, 반환형에 대한 변수를 스택에 생성한다.
따라서 함수명 뒤에 매개변수가 선언되어 있어야 사용 가능하다.

클래스 멤버 함수를 함수 포인터로 만들어 사용하려하면 극단적으로 사용 범위가 줄어든다.
멤버 함수를 사용하기 위해서는 객체를 통해 접근해야하기 때문이다.

선언되어 있는 함수포인터형의 정보(반환형, 매개변수, 자료형)이 완전 일치해야 사용 가능하다.
그렇지만 함수 포인터형 사이에는 캐스팅이 가능하다.
int(*Func1)(int), float(*Func2)(float)
Func1 = (int(*) (int))Func2;

class AAA
{
void Func1() { ; }
static void Func2() { ; }
};

int main()
{
AAA a;
a.Func1();

void(*pFunc1)() = &AAA::Func1;
a.pFunc1();
(a.*pFunc1)();

void(*pFunc2)() = &AAA::Func2;

}
*/


//std::function<void(*)> pFunc;

/*함수 객체 : 실제로는 객체이지만 보이기는 함수처럼 보이는 객체
class AAA
{
public:
int operator()(int n)
{
return (n + 1);
}
};

AAA a;
int n = a(1);
*/