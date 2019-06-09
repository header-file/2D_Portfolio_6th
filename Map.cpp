#include "Game.h"
#include "SingletonBase.h"
#include "Map.h"


Map::Map()
{
}

Map::~Map()
{
}

bool Map::Init()
{
	back = IMAGEMANAGER->FindImage("MapBackground");
	rooms[0].roomImg = IMAGEMANAGER->FindImage("Room1Map");
	rooms[1].roomImg = IMAGEMANAGER->FindImage("Room2Map");
	rooms[2].roomImg = IMAGEMANAGER->FindImage("Room3Map");
	rooms[3].roomImg = IMAGEMANAGER->FindImage("Room4Map");
	rooms[4].roomImg = IMAGEMANAGER->FindImage("Room5Map");
	rooms[5].roomImg = IMAGEMANAGER->FindImage("Room6Map");
	rooms[6].roomImg = IMAGEMANAGER->FindImage("Room7Map");
	rooms[7].roomImg = IMAGEMANAGER->FindImage("Room8Map");
	rooms[8].roomImg = IMAGEMANAGER->FindImage("Room9Map");
	rooms[9].roomImg = IMAGEMANAGER->FindImage("Room10Map");

	rooms[0].playerPos = RectMakeCenter(R1X, R1Y, POSWIDTH, POSHEIGHT);
	rooms[1].playerPos = RectMakeCenter(R2X, R2Y, POSWIDTH, POSHEIGHT);
	rooms[2].playerPos = RectMakeCenter(R3X, R3Y, POSWIDTH, POSHEIGHT);
	rooms[3].playerPos = RectMakeCenter(R4X, R4Y, POSWIDTH, POSHEIGHT);
	rooms[4].playerPos = RectMakeCenter(R5X, R5Y, POSWIDTH, POSHEIGHT);
	rooms[5].playerPos = RectMakeCenter(R6X, R6Y, POSWIDTH, POSHEIGHT);
	rooms[6].playerPos = RectMakeCenter(R7X, R7Y, POSWIDTH, POSHEIGHT);
	rooms[7].playerPos = RectMakeCenter(R8X, R8Y, POSWIDTH, POSHEIGHT);
	rooms[8].playerPos = RectMakeCenter(R9X, R9Y, POSWIDTH, POSHEIGHT);
	rooms[9].playerPos = RectMakeCenter(R10X, R10Y, POSWIDTH, POSHEIGHT);

	for (int i = 0; i < MAXROOM; i++)
	{
		rooms[i].isFind = false;
		rooms[i].isHere = false;
	}

	alpha = 0;
	return true;
}

void Map::Release()
{
}

void Map::Update()
{
	alpha += 250;
}

void Map::Render(HDC hdc)
{
	back->Render(hdc);
	for (int i = 0; i < MAXROOM; i++)
	{
		if (rooms[i].isHere == true)
			rooms[i].roomImg->AlphaRender(hdc, alpha);
		else if (rooms[i].isFind == true)
			rooms[i].roomImg->Render(hdc);
	}
}

void Map::ResetPosition()
{
	for (int i = 0; i < MAXROOM; i++)
		rooms[i].isHere = false;
}

std::string Map::GetFindIndex()
{
	std::string str;

	for (int i = 0; i < MAXROOM; i++)
	{
		if (rooms[i].isFind == true)
		{
			str += std::to_string(i);
			str += ", ";
		}
	}

	return str;
}
