#pragma once
#include "BackBuffer.h"

class BackBuffer;


class GameNode
{
private:
	BackBuffer * _backBuffer;

	bool		 _managerInit;

	void SetBackBuffer();  //�ٹ��۸� �������� �����Ͽ� �ʱ�ȭ
public:
	
	GameNode();
	virtual ~GameNode();

	virtual bool Init();
	virtual bool Init(bool mInit);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	BackBuffer* GetBackBuffer() { return _backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

