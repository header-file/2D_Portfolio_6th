#pragma once

#define BOSSWIDTH 100
#define BOSSHEIGHT 150
#define MAXBULLET 9
#define MAXALL 8
#define ALLHEIGHT 122
#define BOSSDEFAULTY 300
#define DUSTWIDTH 64

class Bullet;

class Boss
{
private:
	Image*		img;
	Animation*	ani;
	Image*		damageNumber;

	Bullet*		bullet[MAXBULLET];

	RECT		collision;

	POINT		pos;
	int			speed;
	int			dir;

	Enemy_State	state;

	DWORD		standardTime, nowTime, damTime;
	int			realDamage;

	bool		isStart;

	int			hp;
	int			atk;
	int			def;
	int			exp;

	bool		isAlive;

public:
	Boss();
	~Boss();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void ChangeState(Enemy_State _state);
	void AniPause();
	void Damage(int _damage);
	bool CheckTime();

	inline void SetPos(POINT _pos) { pos = _pos; }
	inline void SetisStart(bool _b) { isStart = _b; }

	inline RECT GetRect() { return collision; }
	inline Bullet* GetBullet(int _num) { return bullet[_num]; }
	inline bool GetisAlive() { return isAlive; }
	inline int GetAtk() { return atk; }
};

