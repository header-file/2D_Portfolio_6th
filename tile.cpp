#include "Game.h"
#include "tile.h"

tile::tile() : totalCost(0.f), costFromStart(0.f), costToGoal(0.f),
				parentNode(NULL), idX(0), idY(0), isOpen(true)
{
}

tile::~tile()
{
}

bool tile::Init(int idx, int idy)
{
	color = RGB(255, 150, 0);
	brush = CreateSolidBrush(color);
	
	pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	center = PointMake(idx * TILESIZE + (TILESIZE / 2), idy * TILESIZE + (TILESIZE / 2));

	idX = idx;
	idY = idy;

	rc = RectMakeCenter(center.x, center.y, TILESIZE, TILESIZE);

	return true;
}

void tile::Release()
{
	DeleteObject(brush);
	DeleteObject(pen);
}

void tile::Update()
{
}

void tile::Render(HDC hdc)
{
	SelectObject(hdc, (HBRUSH)brush);
	FillRect(hdc, &rc, brush);

	SelectObject(hdc, (HPEN)pen);
	RectangleMake(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

void tile::setColor(COLORREF _color)
{
	DeleteObject(brush);

	color = _color;
	brush = CreateSolidBrush(color);
}
