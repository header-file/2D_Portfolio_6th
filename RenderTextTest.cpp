#include "Game.h"
#include "RenderTextTest.h"
#include "FontTest.h"


RenderTextTest::RenderTextTest()
{
	
}

RenderTextTest::~RenderTextTest()
{
}

bool RenderTextTest::Init()
{
	pTest = new FontTest;
	assert(pTest != NULL);

	pTest->Init();

	return true;
}

void RenderTextTest::Release()
{
	pTest->Release();
	SAFE_DELETE(pTest);
}

void RenderTextTest::Update()
{
	pTest->Update();
}

void RenderTextTest::Render(HDC hdc)
{
	pTest->RenderTest(hdc, TEXT("Adobe"), TEXT("Hello World!!"), &pTest->GetPosition(), RGB(125, 0, 125));

	POINT pos = { 200, 200 };
	pTest->RenderTest(hdc, TEXT("Adobe"), TEXT("Çï·Î ¿ùµå!!"), &pos, RGB(255, 0, 125));

	pTest->RenderNumber(hdc, 200, 300);
}
