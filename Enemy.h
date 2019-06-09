#pragma once

#define ZOMBIEWIDTH 80
#define ZOMBIEHEIGHT 100
#define BATWIDTH 16
#define BATHEIGHT 20
#define ARCHERWIDTH 20
#define ARCHERHEIGHT 100
#define PERSEPHONEWIDTH 24
#define PERSEPHONEHEIGHT 80
#define KICKWIDTH 80
#define KICKHEIGHT 20
#define KICKYMODIFY 28

class Bullet;

class Enemy
{
private:
	Image*		img;
	Animation*	ani;
	Image*		damageNumber;

	Bullet*		bullet;

	RECT		collision;
	RECT		searchArea;
	RECT		hitBox;
	POINT		pos;
	int			speed;

	DIRECTION	dir;

	Enemy_Type	type;
	Enemy_State	state;

	int			hp;
	int			atk;
	int			def;
	int			exp;

	DWORD		nowTime, standardTime;
	int			realDamage;

	bool		isAlive;

public:
	Enemy();
	~Enemy();

	bool Init(Enemy_Type _type);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void ChangeState(Enemy_State _state);
	void AniPause();
	void Damage(int _damage);
	void CheckSearch(POINT _pos);
	void CheckDir();

	inline void SetPos(POINT _pos) { pos = _pos; }
	inline void SetDir(DIRECTION _dir) { dir = _dir; }

	inline int GetImgHeight() { return img->GetFrameHeight(); }
	inline POINT GetPos() { return pos; }
	inline RECT GetRect() { return collision; }
	inline RECT GetArea() { return searchArea; }
	inline RECT GetHitBox() { return hitBox; }
	inline Enemy_State GetState() { return state; }
	inline Enemy_Type GetType() { return type; }
	inline Bullet* GetBullet() { return bullet; }
	inline int GetAtk() { return atk; }
	inline int GetExp() { return exp; }
	inline bool GetisAlive() { return isAlive; }
	inline DIRECTION GetDir() { return dir; }
};

