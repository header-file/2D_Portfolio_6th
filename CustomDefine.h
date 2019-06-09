#pragma once

//사용자 정의 자료형
enum DIRECTION
{
	LEFT = -1,
	RIGHT = 1,
};

enum PLAYER_STATE
{
	STAND,
	RUN,
	JUMP,
	JUMPATTACK,
	SIT,
	ATTACK,
	DAMAGE,
	DIE,
};

enum Col_Type
{
	RECT_COL = 0,
	PIXEL_COL = 1,
	FOOTHOLD_COL = 2,
};

enum Enemy_Type
{
	ZOMBIE = 0,
	BAT = 1,
	ARCHER = 2,
	PERSEPHONE = 3,
};

enum Enemy_State
{
	E_STAND = 0,
	E_MOVE = 1,
	E_ATTACK = 2,
	E_DIE = 3,
	ZOMBIE_RISEUP = 4,
	ZOMBIE_RISEDOWN = 5,
	ARCHER_RELOAD = 6,
	PERSEPHONE_BOW = 7,
	PERSEPHONE_COMBAT = 8,
	BOSS_MELEE_READY = 9,
	BOSS_MELEE = 10,
	BOSS_RANGE = 11,
	BOSS_ALL_READY = 12,
	BOSS_ALL = 13
};

enum Bullet_Type
{
	ARCHER_ARROW = 0,
	BOSS_RANGEBULLET = 1,
	BOSS_ALLBULLET = 2,
};

struct ColBox
{
	RECT		collision;
	Col_Type	type;
};



struct SPHERE
{
	float x, y;
	float r;
};

//원 관련
#define PI			3.141592654f
#define PI2			PI * 2


//이미지 투명 처리용
#define COLOR_M		RGB(255, 0, 255)


//Tile 관련
#define TILESIZE	32

#define TILEX		20
#define TILEY		20

#define TILESIZEX	TILESIZE * TILEX
#define TILESIZEY	TILESIZE * TILEY

#define SAMPLETILEX	20
#define SAMPLETILEY 9



//사용자 정의 타입
typedef void(*CALL_FUNC)();
typedef void(*CALL_FUNC_PARAM)(void*);


//Extern
extern HWND			_hWnd;
extern HINSTANCE	_hInst;
extern POINT		_ptMouse;
extern RECT			_rcClient;

//#if defined(_MOVIE_TEST)
extern HWND			_hWndAvi;
//#endif //