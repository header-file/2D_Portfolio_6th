#include "Game.h"
#include "AstarTest.h"
#include "tile.h"

AstarTest::AstarTest()
{
}

AstarTest::~AstarTest()
{
}

bool AstarTest::Init()
{
	if (!SetTile())
		return false;

	count = 0;
	start = false;

	return true;
}

void AstarTest::Release()
{
}

void AstarTest::Update()
{
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		PathFinder(currentTile);
	}
	if (start)
	{
		count++;
		if (count % 5 == 0)
		{
			PathFinder(currentTile);
			count = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);
		
		for (int i = 0; i < vTotalList.size(); ++i)
		{
			if (PtInRect(&vTotalList[i]->getRect(), _ptMouse))
			{
				if (vTotalList[i]->getAttribute() == TEXT("Start"))
					continue;
				if (vTotalList[i]->getAttribute() == TEXT("End"))
					continue;

				vTotalList[i]->setIsOpen(false);
				vTotalList[i]->setAttribute(TEXT("Wall"));
				vTotalList[i]->setColor(RGB(230, 140, 200));
				break;

			}
		}
	}
}

void AstarTest::Render(HDC hdc)
{
	for (int i = 0; i < vTotalList.size(); ++i)
	{
		vTotalList[i]->Render(hdc);
	}
}

bool AstarTest::SetTile()
{
	startTile = new tile;
	startTile->Init(4, 12);
	startTile->setAttribute(TEXT("Start"));

	endTile = new tile;
	endTile->Init(20, 12);
	endTile->setAttribute(TEXT("End"));

	currentTile = startTile;

	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			if (j == startTile->getIdX() && i == startTile->getIdY())
			{
				startTile->setColor(RGB(0, 255, 255));
				vTotalList.push_back(startTile);
				continue;
			}

			if (j == endTile->getIdX() && i == endTile->getIdY())
			{
				endTile->setColor(RGB(10, 125, 55));
				vTotalList.push_back(endTile);
				continue;
			}

			tile* node = new tile;
			node->Init(j, i);
			vTotalList.push_back(node);
		}
	}

	return true;
}

AstarTest::vTile AstarTest::AddOpenList(tile * _currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			tile* node = vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			if (!node->getIsOpen())
				continue;
			if (node->getAttribute() == TEXT("Start"))
				continue;
			if (node->getAttribute() == TEXT("Wall"))
				continue;

			node->setParentNode(currentTile);

			bool addObj = true;

			for (viOpenList = vOpenList.begin(); viOpenList != vOpenList.end(); ++viOpenList)
			{
				if (*viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != TEXT("End"))
				node->setColor(RGB(128, 64, 28));

			if (!addObj)
				continue;

			vOpenList.push_back(node);
		}
	}
	return vOpenList;
}

void AstarTest::PathFinder(tile * _currentTile)
{
	float tempTotalCost = 5000.f;

	tile* tempTile = NULL;

	for (int i = 0; i < AddOpenList(currentTile).size(); ++i)
	{
		//G
		vOpenList[i]->setCostToGoal(
			(abs(endTile->getIdX() - vOpenList[i]->getIdX()) + abs(endTile->getIdY() - vOpenList[i]->getIdY())) * 10);

		//H
		POINT center1 = vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = vOpenList[i]->getCenter();

		//F
		vOpenList[i]->setCostFromStart((UTIL::getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);
		vOpenList[i]->setTotalCost(vOpenList[i]->getCostToGoal() + vOpenList[i]->getCostFromStart());

		//F의 최소값
		if (tempTotalCost > vOpenList[i]->getTotalCost())
		{
			tempTotalCost = vOpenList[i]->getTotalCost();
			tempTile = vOpenList[i];
		}

		bool addObj = true;

		//iterator 미사용 1
		std::for_each(vOpenList.begin(), vOpenList.end(), [tempTile, &addObj](auto a) {
			if (a == tempTile)
			{
				addObj = false;
				return;
			}
		});

		//iterator 미사용 2
		/*for (auto a : vOpenList)
		{
			if (a == tempTile)
			{
				addObj = false;
				break;
			}
		}*/

		//iterator 사용
		/*for (viOpenList = vOpenList.begin(); viOpenList != vOpenList.end(); ++viOpenList)
		{
			if (*viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}*/
		
		vOpenList[i]->setIsOpen(false);

		if (!addObj)
			continue;

		vOpenList.push_back(tempTile);
	}

	if (tempTile->getAttribute() == TEXT("End"))
	{
		while (currentTile->getParentNode() != NULL)
		{
			currentTile->setColor(RGB(22, 14, 128));
			currentTile = currentTile->getParentNode();
		}
		return;
	}

	vCloseList.push_back(tempTile);

	for (viOpenList = vOpenList.begin(); viOpenList != vOpenList.end(); ++viOpenList)
	{
		if (*viOpenList == tempTile)
		{
			viOpenList = vOpenList.erase(viOpenList);
			break;
		}
	}

	currentTile = tempTile;
	
	PathFinder(currentTile);		//재귀 호출

	//기본적으로 호출 규약에 맞춰 사용 변수 등의 크기에 따라 스택을 할당
	//함수가 종료가 되어야 스택에 쌓인 영역을 삭제
	//재귀 함수는 함수가 종료되기 전에 계속 호출하기 때문에
	//재귀 함수가 반복되면 스택 오버플로우가 발생
	//그렇기 때문에 이 방식은 매우 큰 영역에서의 길 찾기로는 사용할 수 없다.
}
