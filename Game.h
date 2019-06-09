#pragma once
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#pragma warning(disable:4996)

//winAPI 관련 헤더
#include <windows.h>
#include <Vfw.h>



// 시스템 헤더
#include <assert.h>
#include <tchar.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <functional>



//추가 헤더
#include "CustomDefine.h"
#include "RandomFunction.h"
#include "commonMacroFunction.h"
#include "CollisionFunction.h"
#include "GameNode.h"
#include "Util.h"
#include "Image.h"
#include "Animation.h"
#include "Timer.h"
#include "Camera.h"
#include "Player.h"
#include "Equipment.h"
#include "Menu.h"
#include "Map.h"


using std::string;
using std::vector;
using std::list;
using std::map;


//사용자 정의 매니저
#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextData.h"
#include "AniManager.h"

//멀티바이트와 유니코드 문자셋 변환 처리
#if defined(_UNICODE)
	typedef std::wstring	tstring;		//std::basic_string<wchar>
#else
	typedef std::string		tstring;		//std::basic_string<char>
#endif


//메모리 해제 매크로
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->Release(); (p) = NULL;}}



//싱글턴 객체 매크로
#define RAND				RandomFunction::getSingleton()
#define CAMERA				Camera::getSingleton()
#define KEYMANAGER			KeyManager::getSingleton()
#define IMAGEMANAGER		ImageManager::getSingleton()
#define TIMEMANAGER			TimeManager::getSingleton()
#define EFFECTMANAGER		EffectManager::getSingleton()
#define SCENEMANAGER		SceneManager::getSingleton()
#define SOUNDMANAGER		SoundManager::getSingleton()
#define TXTDATA				TextData::getSingleton()
#define ANIMANAGER			AniManager::getSingleton()
#define PLAYER				Player::getSingleton()
#define EQUIPMENT			Equipment::getSingleton()
#define MENU				Menu::getSingleton()
#define MAP					Map::getSingleton()


//사용자 정의
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#define WINSIZEX		1200
#define WINSIZEY		800
#define WORLDX			22820
#define WORLDY			6190
#define WINSTARTX		100
#define WINSTARTY		100