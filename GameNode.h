#pragma once
#include "BackBuffer.h"

class BackBuffer;


class GameNode
{
private:
	BackBuffer * _backBuffer;

	bool		 _managerInit;

	void SetBackBuffer();  //겟버퍼를 동적으로 생성하여 초기화
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

