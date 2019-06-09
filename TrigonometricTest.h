#pragma once
#include "GameNode.h"

#define	MAX_BULLET 20
 struct _Bullet
{
	float		x, y;
	float		speed;
	float		radius;
	float		angle;
	float		gravity;
	bool		fire;
	int			boundCnt;
};

struct Cannon
{
	POINT		center;			//������ �߽�
	POINT		end;			//������ ��
	float		radius;			//������ ������
	float		angle;			//������ ����
	int			length;			//������ ����
};

struct _Player
{
	float _x, _y;
	float _radius;
	float _angle;
	float _speed;
	float _gunEndX;
	float _gunEndY;
	float _gunLength;
};

class TrigonometricTest : public GameNode
{
	RECT		_rc;
	float		_x, _y;
	float		_angle;

	Cannon _cannon;
	_Bullet _bullet[MAX_BULLET];

	_Player _player;

	int		count;
	int		iIndex;

public:
	TrigonometricTest();
	~TrigonometricTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void BulletFire();
	void BulletMove();

	void BulletCollision();
};

