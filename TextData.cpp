#include "Game.h"
#include "TextData.h"


TextData::TextData()
{
}


TextData::~TextData()
{
}

bool TextData::Init()
{
	return true;
}

void TextData::Release()
{
	getSingleton()->releaseSingleton();
}

void TextData::txtSave(const TCHAR * saveFileName, vector<string> vStr)
{
	HANDLE	file;
	TCHAR	str[128];
	DWORD	write;

	_tcsncpy_s(str, 128, vectorArrayCombine(vStr), 126);

																												//윈도우 API
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);		//Create, 사용, close 형태로 사용한다.
	//핸들, 버퍼, 저장할 사이즈, 저장되어 있는 사이즈, 오버랩 설정
	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

	/*FILE* pf;								C 스타일 함수
	fopen_s(&pf, 경로, 모드);
	fread(buffer, 사이즈, 카운트, pf);
	fwrite(buffer, 사이즈, 카운트, pf);
	fclose(pf);*/
}

TCHAR * TextData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];												//사이즈가 128로 저장 크기에 제한이 있다.
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		_tcsncat_s(str, 128, vArray[i].c_str(), 126);

		if (i + 1 < vArray.size())
		{
			_tcscat_s(str, sizeof(str), ",");
		}
	}

	return str;
}

vector<string> TextData::txtLoad(const TCHAR * loadFileName)
{
	HANDLE file;
	char str[128] = { 0 };
	DWORD read;

	//파일명, 접근 방식, 쉐어 모드 유무, 보안 속성, 생성 방식, 파일 속성, 핸들 템플릿 파일
	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> TextData::charArraySeparation(TCHAR charArray[])
{
	vector<string> vArray;

	const TCHAR* separator = TEXT(",");
	TCHAR* token;

	token = _tcstok(charArray, separator);
	vArray.push_back(token);
	while (NULL != (token = _tcstok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

string TextData::GetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszFile)
{
	return string();
}

void TextData::SetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszData, const TCHAR * pszFile)
{
}

void TextData::RenderNumber(HDC hdc, int number, Image* image, int destX, int destY)
{
	string str = std::to_string(number);

	for (int i = 0; i < str.size(); i++)
	{
		int n = (int)str[i];
		n -= (int)'0';

		image->FrameRender(hdc, destX + image->GetFrameWidth() * i, destY, n, 0);
	}
}

void TextData::RenderDamageCount(HDC hdc, int number, Image * image, int destX, int destY)
{
}
