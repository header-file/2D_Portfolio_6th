#pragma once

#define ARROWWIDTH 60
#define ARROWHEIGHT 4
#define RANGEWIDTH 200
#define RANGEHEIGHT 200
#define ALLWIDTH 25
#define ALLHEIGHT 120
#define RANGECOUNT 3

class Bullet
{
private:
	Image*		img;
	Animation*	ani;

	POINT		pos;
	RECT		collision;
	DIRECTION	dir;

	int			speed;

	Bullet_Type	type;

	int			rangeCount;
	POINT		standardPos;
	float		angle;

	bool		isFire;
	bool		isMove;
	
public:
	Bullet();
	~Bullet();

	bool Init(Bullet_Type _type);
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetFire(POINT _pos);
	void AniPause();
	void SetAngle();

	inline void SetDir(DIRECTION _dir) { dir = _dir; }
	inline void SetPos(POINT _pos) { pos = _pos; }
	inline void SetisFire(bool _b) { isFire = _b; }
	inline void SetisMove(bool _b) { isMove = _b; }

	inline POINT GetPos() { return pos; }
	inline RECT GetRect() { return collision; }
	inline Bullet_Type GetType() { return type; }
	inline bool GetisFire() { return isFire; }
};

