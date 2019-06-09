#pragma once
class TankMap
{
private:
	Tile		tile[TILEX * TILEY];
	POINT		pos;

public:
	TankMap();
	~TankMap();

	bool Load();
	void Render(HDC hdc);

	inline Tile* GetTile() { return tile; }
};

