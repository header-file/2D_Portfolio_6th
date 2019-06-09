#pragma once

class TankMap;

class Tank
{
private:
	TankMap*		tankMap;
	Image*			image;
	POINT			pos;
	RECT			rc;
	int				speed;

public:
	Tank();
	~Tank();

	void Update();
	void Render(HDC hdc);

	void Move();
	void MoveEx();

	POINT GetTilePos(POINT pos);
	POINT GetTilePosEx(RECT rc);

	bool IsWater(POINT pos);
	
	inline void SetTankMap(TankMap* map) { tankMap = map; }
};

