#pragma once
#include "SingletonBase.h"
enum PLAYER_SIZE
{
	BOXWIDTH = 30,
	BOXHEIGHT = 136,
};

#define DAGGERX	62
#define DAGGERY	48
#define SWORDX	60
#define SWORDY	127
#define SPEARX	20
#define SPEARY	54
#define AXEX	50
#define AXEY	126
#define GSWORDX	30
#define GSWORDY	213
#define MAXLEVEL 10
#define HPSTARTX 97
#define HPSTARTY 17
#define HPWIDTH 210
#define HPHEIGHT 32
#define PSTARTX 125
#define PSTARTY 2467

struct StateInfo
{
	int			level;
	int			STR;
	int			CON;
	int			ATK[2];
	int			DEF[2];
	int			maxHP;
	int			hp;
	int			exp;
	int			gold;
	int			leftExp;
};

class Player : public SingletonBase<Player>
{
private:
	Image*		img;
	Animation*	ani;
	Image*		weaponImg;
	Animation*	weaponAni;
	Image*		damageNumber;
	Image*		hpUI;
	Image*		number;

	POINT		pos;

	int			gravity;
	int			jumpPower;

	int			speed;

	bool		jumped;
	bool		gameOver;

	RECT		colBox;
	RECT		hitBox;

	DIRECTION	dir;
	PLAYER_STATE state;

	std::vector<int>	vInventory;
	int					currentWeapon;
	int					currentArmor;

	StateInfo	info;

	int			realDamage;
	DWORD		nowTime, standardTime;

	int			expTable[MAXLEVEL];

	bool		isMovable;

	//hp
	HBRUSH		hBrush, oldBrush;
	RECT		hpBar;

public:
	Player();
	~Player();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Move();
	void Jump();
	void Buy(int _id, int _price);
	void AniPause();
	void ChangeState(PLAYER_STATE _state);
	void FinJump();
	void Damage(int _damage, POINT _effectPos);
	void Die();
	void WeaponChange();
	void ArmorChange();
	void WeaponSet();
	void WeaponStart();
	void WeaponRender(HDC hdc);
	void SetHitBox();
	void PlusExp(int _exp);
	void LevelUp();
	void RenderHPBar(HDC hdc);
	int GetInventoryItem(int _i);
	void AddItem(int _id);
	bool SearchItem(int _id);
	void PresetLevel(int _exp);
	void WChangeTest();

	inline void PlusGold(int _gold) { info.gold += _gold; }
	inline void MinusGold(int _gold) { info.gold -= _gold; }

	inline void SetPos(int _x, int _y) { pos.x = _x; pos.y = _y; }
	inline void SetJumpPower(int _power) { jumpPower = _power; }
	inline void SetHP(int _hp) { info.hp = _hp; }
	inline void ResetJumped() { jumped = false; }
	inline void SetCurWeapon(int _id) { currentWeapon = _id; }
	inline void SetCurArmor(int _id) { currentArmor = _id; }
	inline void SetisMovable(bool _b) { isMovable = _b; }

	inline POINT* GetPos() { return &pos; }
	inline int GetX() { return pos.x; }
	inline int GetY() { return pos.y; }
	inline RECT GetRect() { return colBox; }
	inline RECT GetHitBox() { return hitBox; }
	inline int GetImgWidth() { return img->GetFrameWidth() / 2; }
	inline int GetImgHeight() { return img->GetFrameHeight() / 2; }
	inline DIRECTION GetDir() { return dir; }
	inline PLAYER_STATE GetState() { return state; }
	inline int GetJumpPower() { return jumpPower; }
	inline int GetBoxWidth() { return BOXWIDTH; }
	inline int GetBoxHeight() { return BOXHEIGHT; }
	inline int GetHP() { return info.hp; }
	inline int GetMaxHP() { return info.maxHP; }
	inline int GetAtk() { return info.ATK[0] + info.ATK[1]; }
	inline DWORD GetNowTime() { return nowTime = GetTickCount(); }
	inline DWORD GetStandardTime() { return standardTime; }
	inline int GetCurWeapon() { return currentWeapon; }
	inline int GetCurArmor() { return currentArmor; }
	inline StateInfo* GetInfo() { return &info; }
	inline std::vector<int> GetInventory() { return vInventory; }
	inline int GetGold() { return info.gold; }
	inline int GetSpeed() { return speed; }
};