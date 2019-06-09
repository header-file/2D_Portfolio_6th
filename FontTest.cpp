#include "Game.h"
#include "FontTest.h"



FontTest::FontTest()
{
}


FontTest::~FontTest()
{
}

bool FontTest::Init()
{
	pt = { 100, 100 };
	count = 0;

	//��Ʈ�� ����� ���
	/*
	1. CreateFont()�� ���
	2. CreateFontIndirect()�� ��� - LOGFONT ����ü�� ��Ʈ ������ �����ؾ� �Ѵ�
	3. AddFontResource()�� �ܺ� ��Ʈ�� ����� �� ����ϰ� RemoveFontResource()�� ����
	*/

	//���� �ϳ� ����, ����, ����, ���� ����, ����, �����ü ����, ���� ����, ��Ҽ� ����, ���ڼ�, ��� ��Ȯ��, Ŭ�� ��Ȯ��, ��� ��, �ڰ�, ��Ʈ ���� 
	HFONT font = CreateFont(50, 0, 0, 0, 100, true, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY�߰��"));
	fontMap.insert({ TEXT("�߰��"), font });

	font = CreateFont(40, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
	fontMap.insert({ TEXT("Adobe"), font });

	image = IMAGEMANAGER->AddFrameImage(TEXT("Font"), TEXT("Image/number.bmp"), 490, 50, 10, 1, true, COLOR_M);

	SetNumber(1234567890);

	return true;
}

void FontTest::Update()
{
	count++;

	pt.x -= 5;

	if(pt.x <= -300)
		pt.x = WINSIZEX;
}

void FontTest::Release()
{
	it = fontMap.begin();
	for (; it != fontMap.end(); it++)
	{
		DeleteObject((HFONT)(it->second));
	}
	fontMap.clear();
}

void FontTest::RenderTest(HDC hdc, const string fontName, const string strText, POINT * pos, COLORREF color)
{
	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	it = fontMap.find(fontName);
	if (it != fontMap.end())
	{
		HFONT font = (HFONT)(it->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);

		TextOut(hdc, pos->x, pos->y, strText.c_str(), strText.size());

		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);
	}
}

void FontTest::SetNumber(int num)
{
	number = num;
}

void FontTest::RenderNumber(HDC hdc, int destX, int destY)
{
	str = std::to_string(number);

	for (int i = 0; i < str.size(); i++)
	{
		int n = (int)str[i];
		n -= (int)'0';

		image->FrameRender(hdc, destX + image->GetFrameWidth() * i, destY, n, 0);
	}
}

void FontTest::DrawFont(HDC hdc)
{
}
