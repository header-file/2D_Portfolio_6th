#pragma once
#include "SingletonBase.h"

class TextData : public SingletonBase<TextData>
{
	typedef map<std::pair<string, string>, string> INIMap;
	typedef map<std::pair<string, string>, string>::iterator iINIMap;

	INIMap					mINIData;
	iINIMap					miINIData;

	string					strPath;

	DWORD					standardTime;
	DWORD					nowTime;

public:
	TextData();
	~TextData();

	bool Init();
	void Release();
	
	void txtSave(const TCHAR* saveFileName, vector<string> vStr);
	TCHAR* vectorArrayCombine(vector<string> vArray);

	vector<string> txtLoad(const TCHAR* loadFileName);
	vector<string> charArraySeparation(TCHAR charArray[]);

	string GetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszFile);
	void SetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszData, const TCHAR* pszFile);
	void RenderNumber(HDC hdc, int number, Image* image, int destX, int destY);
	void RenderDamageCount(HDC hdc, int number, Image* image, int destX, int destY);
};

