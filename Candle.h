#pragma once
class Candle
{
private:
	Image*		img;
	Image*		candle4Down;
	Animation*	ani;
	Image*		light;
	Animation*	lAni;

	int			type;

	POINT		pos;
	int			speed;

	bool		isBroke;
	bool		isGot;

	RECT		colBox;

	int			gold;

public:
	Candle();
	~Candle();

	bool Init(int _type, int _x, int _y);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Break();

	inline void SetisGot(bool _b) { isGot = _b; }
	inline void SetPos(POINT _pos) { pos = _pos; }

	inline RECT GetRect() { return colBox; }
	inline bool GetisBroke() { return isBroke; }
	inline bool GetisGot() { return isGot; }
	inline int GetGold() { return gold; }
	inline Image* GetImg() { return img; }
	inline int GetType() { return type; }
	inline POINT GetPos() { return pos; }
	inline int GetSpeed() { return speed; }
};