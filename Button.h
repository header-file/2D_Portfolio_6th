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

//�Լ� ������
/*
CALLBACK �Լ��� �� �� / ������ CALLBACK �Լ��� ���� �� ���
CALLBACK �Լ��� �Լ��� ���� ȣ���ϴ� ���� �ƴ϶� Ư���� ��Ȳ�� �Ǹ� OS�� ȣ��(��׶��忡�� ȣ��)

�Լ��� ����ϱ� ���ؼ��� �Լ���� �Ű������� �ʿ��ϴ�.
�׷��� ���� ��� �Լ��� ������� �𸣸� ������ ����� �߰��ϱⰡ ��ȿ�����̴�.
�׷��� �Լ��� ���� ������ �����͸� ���� ���� ��𼭵� ����� �� �ְ� �� ���� �Լ� ������

��ȯ�� (*�Լ���)(�Ű����� ����Ʈ);

typedef void *Func(int);		//��ȯ���� void*�� �Ϲ� �Լ�
typedef void(*Func)(int);		//�Լ� ������ �ڷ��� ����
Func pFunc = function;			//�Լ��������� ���� = �Լ��� (��ȣ ���� �Լ���)
����� �Լ������ʹ� �Լ� ���·� ��� ����
(*pFunc)(10) ���·� ����ϴ� ���� �Լ� �����͸� �Լ� ���·� ����ϴ� ��Ģ���� ����̳�,
pFunc(10) ������ ȣ�⵵ ���ȴ�.

�Լ� ȣ��ÿ� �Լ� ����η� ���� ���� �Ű������� ���ÿ� �����ϰ�, ��ȯ���� ���� ������ ���ÿ� �����Ѵ�.
���� �Լ��� �ڿ� �Ű������� ����Ǿ� �־�� ��� �����ϴ�.

Ŭ���� ��� �Լ��� �Լ� �����ͷ� ����� ����Ϸ��ϸ� �ش������� ��� ������ �پ���.
��� �Լ��� ����ϱ� ���ؼ��� ��ü�� ���� �����ؾ��ϱ� �����̴�.

����Ǿ� �ִ� �Լ����������� ����(��ȯ��, �Ű�����, �ڷ���)�� ���� ��ġ�ؾ� ��� �����ϴ�.
�׷����� �Լ� �������� ���̿��� ĳ������ �����ϴ�.
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

/*�Լ� ��ü : �����δ� ��ü������ ���̱�� �Լ�ó�� ���̴� ��ü
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