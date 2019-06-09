#include "Game.h"
#include "Tank.h"
#include "TankMap.h"


Tank::Tank()
{
	image = IMAGEMANAGER->AddFrameImage(TEXT("Tank"), TEXT("Image/tank.bmp"), 256, 128, 8, 4, true, COLOR_M);

	//pos.x = TILESIZE;
	//pos.y = TILESIZE;

	rc.left = 0;
	rc.top = 0;
	rc.right = rc.left + image->GetFrameWidth();
	rc.bottom = rc.top + image->GetFrameHeight();

	speed = 5;
}

Tank::~Tank()
{
}

void Tank::Update()
{
	MoveEx();
}

void Tank::Render(HDC hdc)
{
	image->FrameRender(hdc, rc.left, rc.top, image->GetFrameX(), image->GetFrameY());
}

void Tank::Move()
{
	POINT dirPos = pos;

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		dirPos.y -= speed;
		if (!IsWater(GetTilePos(dirPos)))
		{
			pos.y -= speed;
		}
		image->SetFrameY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		dirPos.y += image->GetFrameHeight();
		if (!IsWater(GetTilePos(dirPos)))
		{
			pos.y += speed;
		}
		image->SetFrameY(1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		dirPos.x += image->GetFrameWidth();
		if (!IsWater(GetTilePos(dirPos)))
		{
			pos.x += speed;
		}
		image->SetFrameY(2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		dirPos.x -= speed;
		if (!IsWater(GetTilePos(dirPos)))
		{
			pos.x -= speed;
		}
		image->SetFrameY(3);
	}
}

void Tank::MoveEx()
{
	RECT dirPos = rc;

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		dirPos.top -= speed;
		dirPos.bottom -= speed;
		if (!IsWater(GetTilePosEx(dirPos)))
		{
			rc.top -= speed;
			rc.bottom -= speed;
		}
		image->SetFrameY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		dirPos.top += speed;
		dirPos.bottom += speed;
		if (!IsWater(GetTilePosEx(dirPos)))
		{
			rc.top += speed;
			rc.bottom += speed;
		}
		image->SetFrameY(1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		dirPos.left += speed;
		dirPos.right += speed;
		if (!IsWater(GetTilePosEx(dirPos)))
		{
			rc.left += speed;
			rc.right += speed;
		}
		image->SetFrameY(2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		dirPos.left -= speed;
		dirPos.right -= speed;
		if (!IsWater(GetTilePosEx(dirPos)))
		{
			rc.left -= speed;
			rc.right -= speed;
		}
		image->SetFrameY(3);
	}
}

POINT Tank::GetTilePos(POINT pos)
{
	POINT tilePos = {};
	Tile* tile;
	tile = tankMap->GetTile();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&(tile[i].rc), pos))
		{
			tilePos.x = tile[i].frameX;
			tilePos.y = tile[i].frameY;
		}
	}

	return tilePos;
}

POINT Tank::GetTilePosEx(RECT rc)
{
	POINT tilePos = {};
	Tile* tile;
	tile = tankMap->GetTile();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CollisionRectAndRect(tile[i].rc, rc))
		{
			tilePos.x = tile[i].frameX;
			tilePos.y = tile[i].frameY;

			if (tilePos.x == 4 && tilePos.y == 0)
				return tilePos;
		}
	}

	return tilePos;
}

bool Tank::IsWater(POINT pos)
{
	if (pos.x == 4 && pos.y == 0)
		return true;
	else if (pos.x == 0 && pos.y == 3)
		return true;

	return false;
}
