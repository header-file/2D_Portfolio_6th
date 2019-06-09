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

																												//������ API
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);		//Create, ���, close ���·� ����Ѵ�.
	//�ڵ�, ����, ������ ������, ����Ǿ� �ִ� ������, ������ ����
	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

	/*FILE* pf;								C ��Ÿ�� �Լ�
	fopen_s(&pf, ���, ���);
	fread(buffer, ������, ī��Ʈ, pf);
	fwrite(buffer, ������, ī��Ʈ, pf);
	fclose(pf);*/
}

TCHAR * TextData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];												//����� 128�� ���� ũ�⿡ ������ �ִ�.
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

	//���ϸ�, ���� ���, ���� ��� ����, ���� �Ӽ�, ���� ���, ���� �Ӽ�, �ڵ� ���ø� ����
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
