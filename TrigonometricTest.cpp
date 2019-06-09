#include "Game.h"
#include "TrigonometricTest.h"


TrigonometricTest::TrigonometricTest()
{
}


TrigonometricTest::~TrigonometricTest()
{
}

bool TrigonometricTest::Init()
{
	//cannon init
	_cannon.angle = PI / 2;
	_cannon.length = 80;
	_cannon.radius = 50;
	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = WINSIZEY;
	_cannon.end.x = _cannon.center.x;
	_cannon.end.y = _cannon.center.y;

	count = 0;

	//bullet init
	for (int i = 0; i < MAX_BULLET; i++)
	{
		_bullet[i].radius = 15;
		_bullet[i].speed = 3.f;
		_bullet[i].fire = false;
		_bullet[i].gravity = 0.f;
		_bullet[i].boundCnt = 0;
	}
	

	//player init
	_player._x = WINSIZEX / 2;
	_player._y = WINSIZEY / 2 + 100;
	_player._radius = 40.f;
	_player._angle = PI;
	_player._speed = 5.f;
	_player._gunEndX = _player._x;
	_player._gunEndY = _player._y;
	_player._gunLength = 50.f;


	return true;
}

void TrigonometricTest::Release()
{
}

void TrigonometricTest::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angle < 3.03f)
	{
		_cannon.angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angle > 0.1f)
	{
		_cannon.angle -= 0.04f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		count++;
		BulletFire();
	}

	_cannon.end.x = _cannon.center.x + (cosf(_cannon.angle) * _cannon.length);
	_cannon.end.y = _cannon.center.y + (-sinf(_cannon.angle) * _cannon.length);

	BulletMove();
	BulletCollision();

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player._angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player._angle -= 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player._x += cosf(_player._angle) * _player._speed;
		_player._y += -sinf(_player._angle) * _player._speed;
	}

	_player._gunEndX = _player._x + cosf(_player._angle) * 50.f;
	_player._gunEndY = _player._y + (-sinf(_player._angle) * 50.f);
}

void TrigonometricTest::Render(HDC hdc)
{
	//cannon render
	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y, _cannon.radius * 2, _cannon.radius * 2);
	LineMake(hdc, _cannon.center.x, _cannon.center.y, _cannon.end.x, _cannon.end.y);

	//bullet render
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!_bullet[i].fire)
			continue;

		EllipseMakeCenter(hdc, _bullet[i].x, _bullet[i].y, _bullet[i].radius * 2, _bullet[i].radius * 2);
	}

	//player render
	EllipseMakeCenter(hdc, _player._x, _player._y, _player._radius * 2, _player._radius * 2);
	LineMake(hdc, _player._x, _player._y, _player._gunEndX, _player._gunEndY);
}

void TrigonometricTest::BulletFire()
{
	if (count >= MAX_BULLET)
		count = 0;

	iIndex = count;

	for (int i = 0; i < iIndex; i++)
	{
		if (!_bullet[i].fire)
		{
			_bullet[i].fire = true;
			_bullet[i].x = _cannon.center.x + (cosf(_cannon.angle) * (_cannon.length + _bullet[i].radius));
			_bullet[i].y = _cannon.center.y + (-sinf(_cannon.angle) * (_cannon.length + _bullet[i].radius));
			_bullet[i].angle = _cannon.angle;
		}
	}
}

void TrigonometricTest::BulletMove()
{
	if (count >= MAX_BULLET)
		count = 0;
	iIndex = count;

	for (int i = 0; i < 20; i++)
	{
		if (_bullet[i].fire)
		{
			_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
			_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;

			if (_bullet[i].x <= _bullet[i].radius || _bullet[i].x >= WINSIZEX - _bullet[i].radius)
			{
				_bullet[i].angle = PI - _bullet[i].angle;
				_bullet[i].boundCnt++;
			}
			if (_bullet[i].y <= _bullet[i].radius || _bullet[i].y >= WINSIZEY - _bullet[i].radius)
			{
				_bullet[i].angle = PI2 - _bullet[i].angle;
				_bullet[i].boundCnt++;
			}

			if (_bullet[i].boundCnt >= 3)
			{
				//_bullet[i].fire = false;
				_bullet[i].boundCnt = 0;;
			}
		}
	}
}

void TrigonometricTest::BulletCollision()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		for (int j = i + 1; j < MAX_BULLET; j++)
		{
			if (_bullet[i].radius * 2 < UTIL::getDistance(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y))
			{
				continue;
			}

			_bullet[i].angle = UTIL::getAngle(_bullet[j].x, _bullet[j].y, _bullet[i].x, _bullet[i].y);
			_bullet[j].angle = UTIL::getAngle(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y);
		}
	}
}


