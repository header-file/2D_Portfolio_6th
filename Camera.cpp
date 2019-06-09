#include "Game.h"
#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
	SAFE_DELETE(pPos);
}

bool Camera::Init(POINT * _pt, const RECT & _client, const RECT & _world)
{
	if (_pt == NULL)
		return false;
	
	pTarget = _pt;

	rcWorld = _world;
	rcClient = _client;

	pPos = new POINT;
	pPos->x = 0;
	pPos->y = 0;

	return true;
}

void Camera::Update()
{
	if (pTarget == NULL)
	{
		pPos->x = 0;
		pPos->y = 0;
		return;
	}

	if((*pTarget).x > rcClient.right / 2)
		pPos->x = (*pTarget).x - rcClient.right / 2;
	if((*pTarget).y > rcClient.bottom / 2)
		pPos->y = (*pTarget).y - rcClient.bottom / 2;

	if (pPos->x < 0)
		pPos->x = 0;
	if (pPos->y < 0)
		pPos->y = 0;
	if (pPos->x > rcWorld.right - rcClient.right)
		pPos->x = rcWorld.right - rcClient.right;
	if (pPos->y > rcWorld.bottom - rcClient.bottom)
		pPos->y = rcWorld.bottom - rcClient.bottom;
}
