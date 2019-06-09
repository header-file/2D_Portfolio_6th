#include "Game.h"
#include "Xml.h"
#include "StartScene.h"


StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	backGround = IMAGEMANAGER->FindImage("StartBackground");
	ani = ANIMANAGER->FindAni("Main");
	select = IMAGEMANAGER->FindImage("NewGame");

	ANIMANAGER->Start("Main");
	SOUNDMANAGER->Play(TEXT("MainBgm"), 1.0f);
	
	mode = NEW_GAME;
	return true;
}

void StartScene::Release()
{
}

void StartScene::Update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		select = IMAGEMANAGER->FindImage("LoadGame");
		mode = LOAD_GAME;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		select = IMAGEMANAGER->FindImage("NewGame");
		mode = NEW_GAME;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SceneChange(mode);
	}
}

void StartScene::Render(HDC hdc)
{
	backGround->AniRender(hdc, 0, 0, ani);
	select->Render(hdc, SELECTX - select->GetWidth() / 2, SELECTY - select->GetHeight() / 2);
}

void StartScene::Load()
{
	XmlDocument* doc = new XmlDocument;
	doc->LoadFile("Save.xml");
	assert(doc != NULL);

	XmlElement* data = doc->FirstChildElement("SavedData");

	XmlElement* exp = NULL;
	exp = data->FirstChildElement();
	PLAYER->PresetLevel(exp->UnsignedAttribute("value"));

	XmlElement* inventory = NULL;
	inventory = exp->NextSiblingElement("Inventory");
	std::string str = inventory->Attribute("id");
	
	char ch[32] = { 0, };
	std::strcpy(ch, str.c_str());

	const TCHAR* separator = TEXT(",");
	TCHAR* token;

	token = _tcstok(ch, separator);
	if (atoi(token) != 0)
		PLAYER->AddItem(atoi(token));

	while (NULL != (token = _tcstok(NULL, separator)))
	{
		if (atoi(token) != 0)
			PLAYER->AddItem(atoi(token));
	}

	XmlElement* nowEquip = NULL;
	nowEquip = inventory->NextSiblingElement("Equipment");
	PLAYER->SetCurWeapon(nowEquip->UnsignedAttribute("weapon"));
	PLAYER->WeaponChange();
	PLAYER->SetCurArmor(nowEquip->UnsignedAttribute("armor"));
	PLAYER->ArmorChange();

	XmlElement*	gold = NULL;
	gold = nowEquip->NextSiblingElement("Gold");
	PLAYER->PlusGold(gold->UnsignedAttribute("value"));

	XmlElement* map = NULL;
	map = gold->NextSiblingElement("Map");
	str = map->Attribute("id");
	std::strcpy(ch, str.c_str());
	token = _tcstok(ch, separator);
	MAP->SetisFind(atoi(token));

	while (NULL != (token = _tcstok(NULL, separator)))
			MAP->SetisFind(atoi(token));

	delete doc;
}

void StartScene::SceneChange(GAME_MODE _mode)
{
	ANIMANAGER->Pause("Main");
	SOUNDMANAGER->Pause(TEXT("MainBgm"));
	SOUNDMANAGER->Play(TEXT("Bgm"), 0.5f);
	PLAYER->Init();
	PLAYER->SetisMovable(true);

	switch (_mode)
	{
	case NEW_GAME:
		SCENEMANAGER->ChangeScene(TEXT("R1"));
		MAP->SetisFind(0);
		MAP->ResetPosition();
		MAP->SetisHere(0);
		break;
	case LOAD_GAME:
		Load();
		SCENEMANAGER->ChangeScene(TEXT("R6"));
		PLAYER->SetPos(WINSIZEX / 2, 720 - PLAYER->GetBoxHeight() / 2);
		MAP->ResetPosition();
		MAP->SetisHere(5);
		break;
	}
}
