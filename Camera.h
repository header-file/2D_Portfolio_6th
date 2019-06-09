#pragma once
#include "SingletonBase.h"

class Camera : public SingletonBase<Camera>
{
	POINT*		pTarget;
	POINT*		pPos;

	RECT		rcClient;
	RECT		rcWorld;

public:
	Camera();
	~Camera();
	
	void setTargetPos(POINT* _pt) { pTarget = _pt; }
	void setPosition(POINT* _pt) { pPos = _pt; }

	const POINT* getTargetPos() const { return pTarget; }
	const POINT* getPosition() const { return pPos; }

	void setClientRect(const RECT& _rt) { rcClient = _rt; }
	void setWorldRect(const RECT& _rt) { rcWorld = _rt; }

	const RECT& getClientRect() const { return rcClient; }
	const RECT& getWorldRect() const { return rcWorld; }

	bool operator==(const POINT* pObj) { return pTarget == pObj; }
	bool operator!=(const POINT* pObj) { return pTarget != pObj; }

	bool Init(POINT* _pt, const RECT& _client, const RECT& _world);

	void Update();
};

