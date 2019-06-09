#pragma once

typedef map<string, HFONT> FONTMAP;

class FontTest
{
	FONTMAP				fontMap;
	FONTMAP::iterator	it;

	POINT	pt;
	int		count;

	Image*	image;
	int		number;
	string	str;

public:
	FontTest();
	~FontTest();

	bool Init();
	void Update();
	void Release();
	void RenderTest(HDC hdc, const string fontName, const string strText, POINT* pos, COLORREF color);

	inline POINT GetPosition() { return pt; }

	void SetNumber(int num);
	void RenderNumber(HDC hdc, int destX, int destY);

	void DrawFont(HDC hdc);
};

