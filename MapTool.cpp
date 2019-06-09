#include "Game.h"
#include "MapTool.h"


MapTool::MapTool()
{
	currentTile.x = 0;
	currentTile.y = 0;
}

MapTool::~MapTool()
{
}

bool MapTool::Init()
{
	if (WINSIZEX < 1300)
		return false;

	IMAGEMANAGER->AddFrameImage(TEXT("Tile"), TEXT("Image/maptiles.bmp"), 640, 288, SAMPLETILEX, SAMPLETILEY, true, COLOR_M);

	MapToolSetup();

	currentTile.x = 2;
	currentTile.y = 0;

	return true;
}

void MapTool::Release()
{
}

void MapTool::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);
		ClickSample();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);
		ClickMap();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SaveTile();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		LoadTile();
	}
}

void MapTool::Render(HDC hdc)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->FrameRender(TEXT("Tile"), hdc, tile[i].rc.left, tile[i].rc.top, tile[i].frameX, tile[i].frameY);
	}

	IMAGEMANAGER->Render(TEXT("Tile"), hdc, (WINSIZEX - SAMPLETILEX * TILESIZE), 0);

#if defined(_DEBUG)
	for (int i = 0; i < TILEX; i++)
		LineMake(hdc, i * TILESIZE, 0, i * TILESIZE, TILEY*TILESIZE);
	for (int i = 0; i < TILEY; i++)
		LineMake(hdc, 0, i * TILESIZE, TILEX * TILESIZE, i * TILESIZE);
#endif //
}

void MapTool::MapToolSetup()
{
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			sampleTile[i * SAMPLETILEX + j].frameX = j;
			sampleTile[i * SAMPLETILEX + j].frameY = i;

			SetRect(&sampleTile[i * SAMPLETILEX + j].rc, (WINSIZEX - TILESIZE * SAMPLETILEX) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - TILESIZE * SAMPLETILEX) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&tile[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		tile[i].frameX = 2;
		tile[i].frameY = 0;
	}
}

void MapTool::ClickSample()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&sampleTile[i].rc, _ptMouse))
		{
			currentTile.x = sampleTile[i].frameX;
			currentTile.y = sampleTile[i].frameY;
			break;
		}
	}
}

void MapTool::ClickMap()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&tile[i].rc, _ptMouse))
		{
			tile[i].frameX = currentTile.x;
			tile[i].frameY = currentTile.y;

			if (currentTile.x == 4 && currentTile.y == 0)
			{
				tile[i].terrain = TR_WATER;
			}
		}
	}
}

void MapTool::SaveTile()
{
	HANDLE file;
	DWORD write;

	file = CreateFile(TEXT("mapData.map"), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tile, sizeof(Tile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void MapTool::LoadTile()
{
	HANDLE file;
	DWORD read;

	file = CreateFile(TEXT("mapData.map"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(Tile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}
