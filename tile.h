#pragma once
class tile
{
private:
	int			idX;			//타일의 인덱스
	int			idY;

	POINT		center;
	RECT		rc;

	float		totalCost;		//F
	float		costFromStart;	//G
	float		costToGoal;		//H

	bool		isOpen;			//Open 여부

	tile*		parentNode;		//부모 노드

	COLORREF	color;
	HBRUSH		brush;
	HPEN		pen;

	string		attribute;

public:
	tile();
	~tile();

	bool Init(int idx, int idy);
	void Release();
	void Update();
	void Render(HDC hdc);

	//private 멤버에 접근하기 위한 함수
	int getIdX() { return idX; }
	int getIdY() { return idY; }

	void setColor(COLORREF _color);
	
	RECT getRect() { return rc; }

	POINT getCenter() { return center; }
	void setCenter(POINT _center) { center = _center; }

	void setAttribute(string str) { attribute = str; }
	string getAttribute() { return attribute; }

	void setTotalCost(float _totalCost) { totalCost = _totalCost; }
	float getTotalCost() { return totalCost; }

	void setCostFromStart(float _costFromStart) { costFromStart = _costFromStart; }
	float getCostFromStart() { return costFromStart; }

	void setCostToGoal(float _costToGoal) { costToGoal = _costToGoal; }
	float getCostToGoal() { return costToGoal; }

	void setParentNode(tile* t) { parentNode = t; }
	tile* getParentNode() { return parentNode; }

	void setIsOpen(bool _isOpen) { isOpen = _isOpen; }
	bool getIsOpen() { return isOpen; }
};