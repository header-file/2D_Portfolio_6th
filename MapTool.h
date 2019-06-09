#pragma once


class MapTool : public GameNode
{
private:
	POINT		currentTile;

	Tile		sampleTile[SAMPLETILEX * SAMPLETILEY];
	Tile		tile[TILEX * TILEY];

	int			pos[2];

public:
	MapTool();
	~MapTool();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void MapToolSetup();

	void ClickSample();
	void ClickMap();

	void SaveTile();
	void LoadTile();
};

