#pragma once
class tile
{
private:
	int			idX;			//Ÿ���� �ε���
	int			idY;

	POINT		center;
	RECT		rc;

	float		totalCost;		//F
	float		costFromStart;	//G
	float		costToGoal;		//H

	bool		isOpen;			//Open ����

	tile*		parentNode;		//�θ� ���

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

	//private ����� �����ϱ� ���� �Լ�
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