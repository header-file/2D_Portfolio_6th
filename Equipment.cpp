#include "Game.h"
#include "SingletonBase.h"
#include "Xml.h"
#include "Equipment.h"


Equipment::Equipment()
{
}

Equipment::~Equipment()
{
}

bool Equipment::Init()
{
	for (int i = 0; i < 9; i++)
		equipment[i] = new EquInfo;

	//TxtLoad("Items.txt");
	XmlLoad();

	//Image포인터 icon에 각 장비 아이콘 이미지를 저장
	equipment[0]->icon = IMAGEMANAGER->FindImage("DaggerIcon");
	equipment[1]->icon = IMAGEMANAGER->FindImage("LongSwordIcon");
	equipment[2]->icon = IMAGEMANAGER->FindImage("SpearIcon");
	equipment[3]->icon = IMAGEMANAGER->FindImage("AxeIcon");
	equipment[4]->icon = IMAGEMANAGER->FindImage("GreateSwordIcon");
	equipment[5]->icon = IMAGEMANAGER->FindImage("ClothesIcon");
	equipment[6]->icon = IMAGEMANAGER->FindImage("RobeIcon");
	equipment[7]->icon = IMAGEMANAGER->FindImage("LArmorIcon");
	equipment[8]->icon = IMAGEMANAGER->FindImage("IArmorIcon");
	
	return true;
}

void Equipment::Release()
{
	for (int i = 0; i < 9; i++)
	{
		equipment[i] = NULL;
		SAFE_DELETE(equipment[i]);
	}
}

void Equipment::TxtLoad(const TCHAR * loadFileName)
{
	HANDLE file;
	char str[256] = { 0 };
	DWORD read;

	//파일명, 접근 방식, 쉐어 모드 유무, 보안 속성, 생성 방식, 파일 속성, 핸들 템플릿 파일
	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 256, &read, NULL);

	CloseHandle(file);

	//쪼개기
	const TCHAR* separator = TEXT(",");
	TCHAR* token;

	token = _tcstok(str, separator);

	int i = 0;

	while (NULL != (token = _tcstok(NULL, separator)))
	{
		equipment[i]->id = atoi(token);
		token = _tcstok(NULL, separator);
		equipment[i]->name = token;
		token = _tcstok(NULL, separator);
		equipment[i]->atk = atoi(token);
		token = _tcstok(NULL, separator);
		equipment[i]->def = atoi(token);
		token = _tcstok(NULL, separator);
		equipment[i]->price = atoi(token);
		i++;
	}
}

void Equipment::XmlLoad()
{
	XmlDocument* doc = new XmlDocument;
	Xml::XMLError err = doc->LoadFile("item.xml");
	assert(doc != NULL);

	XmlElement* equipments = doc->FirstChildElement("Equipment");			//DOM 방식이라 Tree 구조로 데이터가 들어있다

	XmlElement* equip = NULL;
	equip = equipments->FirstChildElement();

	int i = 0;

	//LCRS 트리와 유사한 방식
	for (; equip != NULL; equip = equip->NextSiblingElement())
	{
		equipment[i]->id = equip->UnsignedAttribute("id");
		equipment[i]->name = equip->Attribute("name");
		equipment[i]->atk = equip->UnsignedAttribute("atk");
		equipment[i]->def = equip->UnsignedAttribute("def");
		equipment[i]->price = equip->UnsignedAttribute("price");

		i++;
	}

	delete doc;
	//이런 식으로 parser를 만들어 데이터를 읽어온다.
}

EquInfo* Equipment::GetInfo(int _id)
{
	for (int i = 0; i < 9; i++)
	{
		if (equipment[i]->id == _id)
			return equipment[i];
	}

	return NULL;
}
