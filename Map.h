#pragma once

#define MAXROOM 10
#define R1X 310
#define R1Y 380
#define R2X 450
#define R2Y	420
#define R3X 430
#define R3Y	380
#define R4X 370
#define R4Y	380
#define R5X 590
#define R5Y	440
#define R6X 650
#define R6Y	460
#define R7X 690
#define R7Y	420
#define R8X 790
#define R8Y	420
#define R9X 850
#define R9Y	420
#define R10X 895
#define R10Y 420
#define POSWIDTH 24
#define POSHEIGHT 24


class Map : public SingletonBase<Map>
{
	struct Room
	{
		Image*	roomImg;
		RECT	playerPos;
		bool	isFind;
		bool	isHere;
	};
	Image*		back;

	Room		rooms[MAXROOM];
	byte		alpha;

public:
	Map();
	~Map();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ResetPosition();
	std::string GetFindIndex();

	inline void SetisFind(int _index) { rooms[_index].isFind = true; }
	inline void SetisHere(int _index) { rooms[_index].isHere = true; }
};

